#include "openglwidget.h"
#include <QDebug>
#include <QDir>
#include <QPainter>
#include <qmath.h>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_initialized = false;
    m_mouseLastPos.setX(-1);
    m_modelRotation_Z = 0;
    m_modelRotation_X = 0;

    m_gridSize = 1000;
}

OpenGLWidget::~OpenGLWidget()
{

}

float f(QVector2D x) {
    x.setX(x.x() * 4.0f);
    x.setY(x.y() * 4.0f);
    return qSin(x.x()*x.x() + x.y()*x.y()) / 10.0f;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1, 0.1, 0.2, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    //glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    buildBasicShader();

    QVector<QVector2D> vec;
    vec << QVector2D(-1., 1.) << QVector2D(1., 1.) <<
           QVector2D(-1., -1.) << QVector2D(-1., -1.) <<
           QVector2D(1., 1.) << QVector2D(1., -1.);

    QVector<QVector2D> vec4;

    for(int i = 0; i < m_gridSize; i++) {
        for(int g = 0; g < m_gridSize; g++) {
            vec4 << QVector2D(1 - i*2.0/m_gridSize, 1 - g*2.0/m_gridSize);
        }
    }

    m_buffer.create();
    m_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_buffer.bind();

    m_buffer.allocate(vec4.constData(), vec4.length()*sizeof(QVector2D));

    m_basicShaderProgram->bind();
    m_vao.create();
    m_vao.bind();
    m_buffer.bind();
    m_basicShaderProgram->enableAttributeArray("pos");
    m_basicShaderProgram->setAttributeBuffer("pos", GL_FLOAT, 0, 2);

    m_index = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_index.create();
    m_index.bind();

    QVector<unsigned int> h;
    for(int i = 0; i < m_gridSize - 1; i++) {
        for(int g = 0; g < m_gridSize - 1; g++) {
            h << (i * m_gridSize + g) << ((i + 1) * m_gridSize + g) << ((i + 1) * m_gridSize + g + 1);
        }
    }

    for(int i = 0; i < m_gridSize - 1; i++) {
        for(int g = 0; g < m_gridSize - 1; g++) {
            h << (i * m_gridSize + g) << ((i + 1) * m_gridSize + g + 1) << (i * m_gridSize + g + 1);
        }
    }

    m_index.allocate(h.constData(), h.length() * sizeof(unsigned int));

    m_vao.release();
    m_buffer.release();
    m_basicShaderProgram->release();

    m_updTimer.setInterval(16);
    connect(&m_updTimer, SIGNAL(timeout()), this, SLOT(update()));
    m_updTimer.start();
    setZoom(1.0);
    connect(this, SIGNAL(zoomChanged(qreal)), this, SLOT(update()));
    m_zoomAnim.setTargetObject(this);
    m_zoomAnim.setPropertyName(QByteArray("zoom"));
    m_zoomAnim.setEasingCurve(QEasingCurve::OutCubic);
    m_zoomAnim.setDuration(200);

    m_initialized = true;
}

void OpenGLWidget::resizeGL(int w, int h)
{
    if(m_initialized) {
        const qreal retinaScale = devicePixelRatio();
        qreal vw = w * retinaScale;
        qreal vh = h * retinaScale;
        glViewport(0, 0, (GLsizei)vw, (GLsizei)vh);
    }
}

void OpenGLWidget::paintGL()
{
    const qreal retinaScale = devicePixelRatio();
    qreal vw = width() * retinaScale;
    qreal vh = height() * retinaScale;

    // Получаем дельту вращения камеры
    // Хочу заметить, что вычисления чисто эмпирические
    m_modelRotation_Z += m_mouseDelta.x()/vw * 20.0;
    m_modelRotation_X += m_mouseDelta.y()/vh * 20.0;

    m_mouseDelta = QPoint(0, 0);

    // Очищаем экран
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT |
            GL_STENCIL_BUFFER_BIT);

    if(!m_initialized)
        return;

    m_basicShaderProgram->bind();

    // matrices work
    QMatrix4x4 mat_projection;
    mat_projection.perspective(45.0f, vw/vh, 0.1f, 100.0f);
    QMatrix4x4 mat_view;

    qreal fo1 = m_modelRotation_Z;
    qreal fo2 = m_modelRotation_X;

    mat_view.lookAt(
                QVector3D(0, 0, zoom()), // camera position [eye]
                QVector3D(0, 0, 0), // looking at [center]
                QVector3D(0, 1, 0)  // up direction [up direct.]
                );

    QQuaternion cam_rot =
            QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), fo2*14)*
            QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), fo1*14);

    mat_view.rotate(cam_rot);

    QMatrix4x4 mat_model;
    mat_model = QMatrix4x4(1.0, 0.0, 0.0, 0.0,
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.0, 0.0, 0.0, 1.0);

    QMatrix4x4 mat_mvp = mat_projection * mat_view * mat_model;

    m_basicShaderProgram->setUniformValue("MVP", mat_mvp);
    m_basicShaderProgram->setUniformValue("MV", mat_view*mat_model);
    m_basicShaderProgram->setUniformValue("NormalMatrix", (mat_view*mat_model).inverted().transposed());

    QVector3D light_pos(0.0, 1, 2.0);

    m_basicShaderProgram->setUniformValue("LightPos", light_pos);

    m_vao.bind();

    m_index.bind();

    glDrawElements(GL_TRIANGLES, (m_gridSize - 1)*(m_gridSize - 1)*3*2, GL_UNSIGNED_INT, 0);

    m_vao.release();
    m_basicShaderProgram->release();

    // Все равно до сюда никто не дочитает, поэтому тут ссылка на все готовые лабы
    // https://goo.gl/SsAhv

    update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent * e)
{
    if(m_mouseLastPos.x() == -1) {
        m_mouseLastPos = e->pos();
        m_mouseDelta = QPoint(0, 0);
    }

    m_mouseDelta = e->pos() - m_mouseLastPos;
    m_mouseLastPos = e->pos();
    this->update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *e)
{
    m_mouseLastPos = e->pos();
    update();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    m_mouseLastPos = e->pos();
    m_mouseDelta = QPoint(0, 0);
}

void OpenGLWidget::wheelEvent(QWheelEvent *e)
{
    if(m_zoomAnim.state() == QPropertyAnimation::Running){
        qreal z;
        m_zoomAnim.stop();
        z = m_zoomAnim.currentValue().toDouble();
        m_zoomAnim.setStartValue(z);
        m_zoomAnim.setEndValue(m_zoomAnim.endValue().toDouble() + e->delta()/120./4.);
        m_zoomAnim.start();
    }
    else {
        m_zoomAnim.setStartValue(zoom());
        m_zoomAnim.setEndValue(zoom() + e->delta()/120./4.);
        m_zoomAnim.start();
    }
    update();
}

void OpenGLWidget::buildBasicShader()
{
    m_basicShaderProgram = new QOpenGLShaderProgram(this);
    m_basicShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                                  ":/shader_basic.vert");
    m_basicShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                                  ":/shader_basic.frag");
    m_basicShaderProgram->link();

}

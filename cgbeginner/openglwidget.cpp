#include "openglwidget.h"
#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_timer.setInterval(10);
    connect(&m_timer, &QTimer::timeout, this, &OpenGLWidget::updateView);
}

OpenGLWidget::~OpenGLWidget()
{

}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);

    //glEnable(GL_CULL_FACE);
//    glFrontFace(GL_CW);
    //glCullFace(GL_BACK);

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendEquation(GL_FUNC_ADD);

    buildBasicShader();

    QVector<QVector2D> vec;
    vec << QVector2D(0, 0.5) << QVector2D(0.5, -0.5) <<
           QVector2D(-0.5, -0.5);

    m_buffer.create();
    m_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_buffer.bind();

    m_buffer.allocate(vec.constData(), vec.length()*sizeof(QVector2D));

    m_basicShaderProgram->bind();
    m_basicShaderProgram->enableAttributeArray("pos");
    m_basicShaderProgram->setAttributeBuffer("pos", GL_FLOAT, 0, 2);
    m_buffer.release();
    m_basicShaderProgram->release();

    m_timer.start();
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

    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT |
            GL_STENCIL_BUFFER_BIT);

    static int i = 0;
    qDebug() << "paintGL" << i++;

    if(!m_initialized)
        return;

    m_basicShaderProgram->bind();

//    m_basicShaderProgram->setUniformValue("MVP", mat_mvp);
//    m_basicShaderProgram->setUniformValue("MV", mat_view*mat_model);
//    m_basicShaderProgram->setUniformValue("NormalMatrix", (mat_view*mat_model).inverted().transposed());

//    m_vao.bind();
    //glDrawArrays(GL_TRIANGLES, 0, m_gridSize*m_gridSize);

    glDrawArrays(GL_TRIANGLES, 0, 3);

//    m_vao.release();
    m_basicShaderProgram->release();
}

void OpenGLWidget::buildBasicShader()
{
    m_basicShaderProgram = new QOpenGLShaderProgram(this);
    m_basicShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                                  ":/shaders/shader_basic.vert");
    m_basicShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                                  ":/shaders/shader_basic.frag");
    m_basicShaderProgram->link();

}

void OpenGLWidget::updateView()
{
    update();
}

#ifndef OPENGLWIGDET_H
#define OPENGLWIGDET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QWheelEvent>

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QVector>

#include <QElapsedTimer>
#include <QTimer>

#include <QPropertyAnimation>
#include <QImage>
#include <QPainter>
#include <QFont>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget();

    qreal zoom() const
    {
        return m_zoom;
    }

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mouseMoveEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void wheelEvent(QWheelEvent *e);

signals:

    void zoomChanged(qreal arg);

public slots:

    void setZoom(qreal arg)
    {
        if (arg < 0.1)
            return;

        if (m_zoom == arg)
            return;

        m_zoom = arg;
        emit zoomChanged(arg);
    }

private:
    Q_PROPERTY(qreal zoom READ zoom WRITE setZoom NOTIFY zoomChanged)

    void buildBasicShader();

    bool m_initialized;

    qreal m_modelRotation_Z;
    qreal m_modelRotation_X;

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_buffer;
    QOpenGLBuffer m_index;

    int m_gridSize;

    QPoint m_mouseLastPos;
    QPoint m_mouseDelta;

    QOpenGLShaderProgram *m_basicShaderProgram;

    QTimer m_updTimer;

    QPropertyAnimation m_zoomAnim;

    qreal m_zoom;
};

#endif // OPENGLWIGDET_H

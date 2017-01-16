#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QVector>

#include <QTimer>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void buildBasicShader();
    void updateView();

    bool m_initialized;
    QTimer m_timer;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_buffer;
    QOpenGLShaderProgram * m_basicShaderProgram;
};

#endif // OPENGLWIDGET_H

# Краткий курс по OpenGL и Qt

## Кратко о курсе

В этом курсе мы будем изучать основы 3D графики на примере OpenGL. Ключевой момент -- __"основы"__.  
Данный документ больше нацелен на практику, чем на теоретические основы. С ними вы можете ознакомиться на лекциях.

# Основы Qt

До этого курс давался на `C` с использованием `glew/glm/glfw`. Сейчас мы решили давать его на `C++/Qt`. Во-первых, это немного упрощает всякий менеджмент ресурсов и прочее за счет использования C++ (снижает количество ошибок (хотя сомнительное утверждение)). Во-вторых, в Qt есть куча готовых классов/функций/методик, которые упрощают разработку приложения. Это и создание окон, и математика, и сериализация, и прочее.

> Qt (произносится ˈkjuːt (кьют) как «cute» или неофициально Q-T (кью-ти)) — кроссплатформенный инструментарий разработки ПО на языке программирования C++. Есть также «привязки» ко многим другим языкам программирования: Python — PyQt, PySide; Ruby — QtRuby; Java — Qt Jambi; PHP — PHP-Qt и другие. - Википедия

__Q:__ Почему C++/Qt, а не C#, JS, Java, <мой любимый язык и фреймворк>?  
__A:__ Прост))00. При выполнении лаб можете использовать любой удобный для вас язык, в котором вы чувствуете себя комфортно.

## Что нам понадобится

Qt SDK, который включает в себя не только библиотеки Qt, но и среду разработки -- Qt Creator. Скачать вы его можете [тут](https://www.qt.io/download-open-source/). Мы будем рассматривать разработку на винде, на других системах будет аналогично.

![](http://dl3.joxi.net/drive/2017/01/13/0004/1919/300927/27/fb048b05a7.png)

Запускаете инсталлер, вход в аккаунт можно скипнуть.
Убедитесь, что в инсталлере отметили следующие штуки:
* Qt 5.7
  * MinGW 5.3.0 32 bit << Это набор библиотек
* Tools
  * MinGW 5.3.0

![](http://dl3.joxi.net/drive/2017/01/13/0004/1919/300927/27/a1d875830c.png)
![](http://dl4.joxi.net/drive/2017/01/13/0004/1919/300927/27/52299eeafb.png)

_Для тех, кто принципиально хочет использовать компилятор от VS: Если у вас уже установлена Visual Studio, то можете вместо MinGW установить библиотеки, соответствующие версии Visual Studio. Важно, чтобы версии библиотек Qt и тулкита Visual Studio совпадали, иначе не заработает._

## Создание простого приложения

Сейчас у нас уже должен быть установлен Qt SDK и Qt Creator. Вы сразу же можете открыть примеры на главной странице Qt Creator и погрузиться в пучины неизведанного.
![](http://dl3.joxi.net/drive/2017/01/13/0004/1919/300927/27/d2400d81e3.png)
Сделаем же небольшое GUI приложение! `Новый проект > Приложение > Приложение Qt Widgets`. Выбирайте комплект `Desktop Qt 5.7.0 MinGW 32 bit` или что-то похожее. В качестве базового класса выберите `QWidget` с именем просто `Widget`. Ура! Мы сделали первый проект! Нажимайте на большую зеленую кнопку и, если вы все сделали верно, появится окошко. Вы можете вручную добавлять разные компоненты на ваш виджет зайдя в редактор UI. Для этого два раза кликните по файлу `widget.ui` слева в проекте.

## Документация

У Qt великолепная документация. Ознакомится с ней вы можете [здесь](http://doc.qt.io/qt-5/index.html). Библиотека разделена на модули. Наиболее интересные для нас сейчас:
* __Qt Core__ - Базовая функциональность, контейнеры, метаобъектная система.
* __Qt GUI__ - Базовые классы для пользовательского интерфейса. Включает в себя классы для работы с OpenGL.
* __Qt Multimedia__ - Классы для поддержки аудио, видео и прочего мультимедиа.
* __Qt Multimedia Widgets__ - Классы, основанные на виджетах, для поддержки мультимедиа.
* __Qt Network__ - Классы для работы с сетью.
* __Qt Widgets__ - Классы виджетов на C++.

#### Qt Core
[Qt Core](http://doc.qt.io/qt-5/qtcore-index.html)  
[Контейнеры: Список, Словарь, Вектор](http://doc.qt.io/qt-5/containers.html)  
[Сигналы и слоты](http://doc.qt.io/qt-5/signalsandslots.html)  
> Signals and slots are used for communication between objects. The signals and slots mechanism is a central feature of Qt and probably the part that differs most from the features provided by other frameworks. Signals and slots are made possible by Qt's meta-object system.

#### Qt GUI
[Qt GUI](http://doc.qt.io/qt-5/qtgui-index.html)  
> The Qt GUI module provides classes for windowing system integration, event handling, OpenGL and OpenGL ES integration, 2D graphics, basic imaging, fonts and text. These classes are used internally by Qt's user interface technologies and can also be used directly, for instance to write applications using low-level OpenGL ES graphics APIs.

#### Qt Widgets
[Пользовательский интерфейс](http://doc.qt.io/qt-5/topics-ui.html)  
> Qt features multiple technologies for creating user interfaces. While it is possible to mix and match these different technologies as needed, one approach is often better suitable for a certain type of user interface than the others. Qt Creator is a good example of an application that mixes different user interface technologies. In fact, it uses the two different approaches described below. Qt Creator uses the traditional Qt Widgets such as menus and dialogs as a basis of the user interface, Qt Quick amongst others for the welcome screen. The following sections provide brief introductions to the available technologies for creating user interfaces, and a comparison table to help choosing the best suitable technology.

[Документация по виджетам](http://doc.qt.io/qt-5/qtwidgets-index.html)  
[Список классов виджетов](http://doc.qt.io/qt-5/qtwidgets-module.html)

## Полезные классы и математика
В ходе изучения OpenGL мы обнаружим, что полезно иметь некие абстракции для таких объектов, как точка, вектор, матрица и прочее.

* __QPoint__ - точка, целочисленные координаты [Документация](http://doc.qt.io/qt-5/qpoint.html)
* __QPointF__ - точка, координаты с плавающей точкой [Документация](http://doc.qt.io/qt-5/qpointf.html)
* __QRect__ - прямоугольник с целочисленными координатами [Документация](http://doc.qt.io/qt-5/qrect.html)
* __QRectF__ - с плавающей точкой [Документация](http://doc.qt.io/qt-5/qrectf.html)
* __QMatrix4x4__ - матрица 4x4 [Документация](http://doc.qt.io/qt-5/qmatrix4x4.html)
* __QQuaternion__ - кватернион [Документация](http://doc.qt.io/qt-5/qquaternion.html)
* __QVector__ - динамический массив [Документация](http://doc.qt.io/qt-5/qvector.html)
* __QVector2D__ - вектор в 2D [Документация](http://doc.qt.io/qt-5/qvector2d.html)
* __QVector3D__ - вектор в 3D [Документация](http://doc.qt.io/qt-5/qvector3d.html)
* __QVector4D__ - вектор в 4D [Документация](http://doc.qt.io/qt-5/qvector4d.html)

# Первое OpenGL приложение

![](http://dl3.joxi.net/drive/2017/01/17/0004/1919/300927/27/18b77646f0.png)

Да, это просто желтый треугольник на черном фоне. Не правда ли круто? Мы рассмотрим базовую структуру OpenGL приложения. Исходник находится в проекте __cgbeginner__. Смелее скачайте его и попробуйте!

В общем-то наша программа будет состоять из одного класса `OpenGLWidget`. Этот класс наследуется от `QOpenGLWidget` и `QOpenGLFunctions`. Первый предоставляет функциональность для отображения OpenGL контента в приложении на Qt, второй же предоставляет кроссплатформенный доступ к OpenGL ES 2.0 API (для того, чтобы вызывать команды OpenGL). Класс [`QOpenGLWidget`](http://doc.qt.io/qt-5/qopenglwidget.html) предоставляет три удобные виртуальные функции для инициализации и отрисовки:  
* [`paintGL()`](http://doc.qt.io/qt-5/qopenglwidget.html#paintGL) - Отрисовывает OpenGL сцену. Вызывается каждый раз, когда виджет обновляется.
* [`resizeGL()`](http://doc.qt.io/qt-5/qopenglwidget.html#resizeGL) - Устанавливаем новые значения преобразований для отображения (ведь размер виджета-то теперь другой). Вызывается каждый раз, когда изменяется размер виджета.
* [`initializeGL()`](http://doc.qt.io/qt-5/qopenglwidget.html#initializeGL) - Инициализация ресурсов OpenGL. Здесь мы загружаем шейдеры, текстурки и прочее. Вызывается до `paintGL()` и `resizeGL` __ОДИН РАЗ__.

## Загрузка контента в OpenGL

Итак, нам нужно отобразить треугольник (или несколько). Для того, чтобы что-то отобразить, нужно это что-то загрузить в OpenGL. Тут нам помогут следующие вещи:
* Vertex Buffer Object (VBO) [оффициальная документация](https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Buffer_Object)
* Vertex Arrays Object (VAO) [оффициальная документация](https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Array_Object)

**Vertex Buffer Object (VBO)** - такая штука, которая хранит кусок данных в OpenGL и используется для хранения вершинных данных. С ее помощью мы загружаем данные об атрибутах вершин из оперативной памяти в видеопамять сразу большими кусками. Обмен данными между оперативной и видеопамятью довольно затратная вещь, и каждый раз отсылать одни и те же данные в процессе отрисовки будет не очень эффективно. Вообще говоря, VBO - это просто разновидность буфера OpenGL (а бывают и другие, например пиксельный буфер или текстурный), который используется для хранения данных вершин.

Кроме положении в пространстве (x, y, z), у вершины могут быть и другие атрибуты, например: uv-координаты (u, v), цвет (r, g, b, a), нормаль (x\`, y\`, z\`), причем не всегда эти атрибуты представляются числами с плавающей точкой, иногда используются целочисленные типы, то есть размер в байтах может быть разный. Можно для каждого атрибута делать отдельный буффер, а можно все запихать в один. Можно расположить в буффере для каждой вершины модели сначала цвет, потом положение, потом нормаль, а можно в другом порядке. И как определить, какой из этих атрибутов как задается и как используется в шейдере? Для этого (и не только) существует **VAO** (не VBO).

**Vertex Array Object (VAO)** - это объект OpenGL, который хранит **формат** вершинных данных и ссылки на буферы, откуда беруться данные. Важно заметить, что он не хранит в себе сами данные, он хранит только формат (а именно, В КАКОМ ВИДЕ (какой тип атрибутов), ОТКУДА (из какого буфера), КУДА (какая переменная в шейдере будет соответствовать атрибуту) и КАК (как они хранятся в буфере)). Обычно на одну модель используется один VAO, при том что у этой модели может быть несколько VBO. В интернете ходит много срачей из-за того, что именно хранит VAO, из-за, возможно, недостаточно четкой документации. Так что если встретите на просторах интернета два диаметрально противоположных мнения, не удивляйтесь (особенно на stackoverflow несколько раз встречал ответы, вводящие в заблуждение и грусть).

Использование большинства объектов в OpenGL происходит следующим образом: для того, чтобы создать объект, вызывается `glGen<Название Объекта>(количество, указатель на переменную, куда будет засунут результат);`, для удаления `glDelete<Название Oбъекта>(количество, указатель на переменную, которая хранит объекты);`, для активации (или для биндинга) `glBind<Название Объекта>(объект)` (бывают и другие параметры). Подробнее можно [почитать в оффициальной документации](https://www.khronos.org/opengl/wiki/OpenGL_Object). Пример:
```c
GLuint vbo;
glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glDeleteBuffers(1, &vbo);
```

В Qt уже есть обертки для этих объектов в виде [`QOpenGLBuffer`](http://doc.qt.io/qt-5/qopenglbuffer.html) и [`QOpenGLVertexArrayObject`](http://doc.qt.io/qt-5/qopenglvertexarrayobject.html). Использование `QOpenGLBuffer`:
```c
QOpenGLBuffer buff;
buff.create(); // создание
buff.setUsagePattern(QOpenGLBuffer::StaticDraw);
buff.bind(); // биндим
buff.allocate(data, dataLength); // берем память в OpenGL и копируем туда данные
// делаем то, что надо
buff.release(); // это не высвобождение памяти!!!!!!!1111 это как бы bind, но наоборот, анбиндим короче (делаем его неактивным)
```

Использование `QOpenGLVertexArrayObject`:
```c
QOpenGLBuffer buff;
QOpenGLShaderProgram * shader;
QOpenGLVertexArrayObject vao;
// пропустим создание буфера и шейдеров
vao.create();
vao.bind();
// задаем расположение атрибутов
buff.bind();
shader->bind();
shader->enableAttributeArray("pos"); // "подключим" сохранение атрибутов для переменной pos (которая в шейдере)
shader->setAttributeBuffer("pos", GL_FLOAT, 0, 2);
buff.release();
shader->release();
vao.release();

...
...
...

// отрисовка
vao.bind();
shader->bind();
glDrawArrays(GL_TRIANGLES, 0, 3); // тип примитива - треугольники, 0 - с самого начала буфера, всего 3 вершины
shader->release();
vao.release();
```

Теперь подробнее рассмотрим, как задаются атрибуты вершин. Предположим, у нас есть массив с заполненными данными вершин для какой-нибудь модели. В одном и том же буфере будут располагаться данные и положения, и цвета для каждой вершины, одна вершина сразу за другой. Рассмотрим пример задания атрибута положения. Я думаю, эта картинка все объяснит:

![](http://dl3.joxi.net/drive/2017/02/05/0004/1919/300927/27/8a1de5dfed.png)

Для задания атрибута цвета нужно следующее: `shader->setAttributeBuffer("color", GL_FLOAT, 3*4, 3, 12);`. Подробнее про `setAttributeBuffer` можно почитать [в оффициальной документации](http://doc.qt.io/qt-5/qopenglshaderprogram.html#setAttributeBuffer).

## Index Buffer

Вместо того, чтобы задавать вершины для каждого треугольника по отдельности, можно задать только уникальные вершины, а треугольники описывать с помощью индексов (номеров) вершин. Это пригождается, когда для гладкой поверхности у нас имеются треугольники, которые переиспользуют одни и те же вершины (вершины с одинаковыми координатами). Хорошее разъяснение дается на сайте [opengl-tutorial.org](http://www.opengl-tutorial.org/ru/intermediate-tutorials/tutorial-9-vbo-indexing/). Картинка взята оттуда же.

![](http://www.opengl-tutorial.org/assets/images/tuto-9-vbo-indexing/indexing1.png)

Для каждого треугольника индекс-буфер содержит три числа: номера трех вершин в буффере вершин. Соответственно, теперь в буфере вершин (VBO) мы задаем уникальные вершины, а в индекс-буфере задаем треугольники. НО: Например, если мы используем в двух треугольниках вершину с номером 1, то и атрибуты у этой вершины (типа нормали) будут одинаковые что в первом, что во втором треугольнике. Это может быть полезно, если мы рисуем гладкую поверхность, но может быть неполезно, если мы рисуем угловатую поверхность вроде квадрата.

Команда отрисовки отличается от обычной `glDrawArrays`. Вместо этого мы используем команду `glDrawElements`.

```
QOpenGLBuffer m_index(QOpenGLBuffer::IndexBuffer); // при создании указываем, что это буфер, который используется для индексов
...
m_index.bind();
//            тип элементов,   количество индексов в индекс-буфере,    тип индексов, отступ от начала индекс-буфера
glDrawElements(GL_TRIANGLES, (m_gridSize - 1)*(m_gridSize - 1)*3*2, GL_UNSIGNED_INT, 0);
```

Пример работы с индекс-буфером, а так же пример работы с матрицами вы найдете в проекте с названием **``cgbeginner-function``**.

![](http://dl3.joxi.net/drive/2017/02/26/0004/1919/300927/27/17eb06ac49.png)

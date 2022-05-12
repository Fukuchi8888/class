#include <cstdio>
#include <cmath>

#define GLFW_INCLUDE_GLU  // GLU���C�u�������g�p����̂ɕK�v
#include <GLFW/glfw3.h>
static const float Pi = std::atan(1.0) * 4.0;

static int WIN_WIDTH = 500;                 // �E�B���h�E�̕�
static int WIN_HEIGHT = 500;                 // �E�B���h�E�̍���
static const char* WIN_TITLE = "OpenGL Course";     // �E�B���h�E�̃^�C�g��

static const float positions[8][3] = {
    { -1.0f, -1.0f, -1.0f },
    {  1.0f, -1.0f, -1.0f },
    { -1.0f,  1.0f, -1.0f },
    { -1.0f, -1.0f,  1.0f },
    {  1.0f,  1.0f, -1.0f },
    { -1.0f,  1.0f,  1.0f },
    {  1.0f, -1.0f,  1.0f },
    {  1.0f,  1.0f,  1.0f }
};

static const float colors[6][3] = {
    { 1.0f, 0.0f, 0.0f },  // ��
    { 0.0f, 1.0f, 0.0f },  // ��
    { 0.0f, 0.0f, 1.0f },  // ��
    { 1.0f, 1.0f, 0.0f },  // �C�G���[
    { 0.0f, 1.0f, 1.0f },  // �V�A��
    { 1.0f, 0.0f, 1.0f },  // �}�[���^
};

static const unsigned int indices[12][3] = {
    { 1, 6, 7 }, { 1, 7, 4 },
    { 2, 5, 7 }, { 2, 7, 4 },
    { 3, 5, 7 }, { 3, 7, 6 },
    { 0, 1, 4 }, { 0, 4, 2 },
    { 0, 1, 6 }, { 0, 6, 3 },
    { 0, 2, 5 }, { 0, 5, 3 }
};

// OpenGL�̏������֐�
void initializeGL() {
    // �w�i�F�̐ݒ� (��)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // �[�x�e�X�g�̗L����
    glEnable(GL_DEPTH_TEST);
}

// OpenGL�̕`��֐�
void paintGL() {
    // �w�i�F�Ɛ[�x�l�̃N���A
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ���W�̕ϊ�
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    static float siyakaku = Pi / 4;
    static float f = 1000.0;
    static float n = 0.1;
    float m_1 = (1 / tan(atan((float)WIN_WIDTH * tan(siyakaku / 2) / 500)));
    float m_2 = (1 / tan(atan((float)WIN_HEIGHT * tan(siyakaku / 2) / 500)));
   

     GLfloat m[16] = {
         m_1,   0,                    0,   0,
           0, m_2,                    0,   0,
           0,   0,   -(f + n) / (f - n),  -1,
           0,   0, -2 * f * n / (f - n),   0
     };
     
    glMultMatrixf(m);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0f, 4.0f, 5.0f,     // ���_�̈ʒu
        0.0f, 0.0f, 0.0f,     // ���Ă����
        0.0f, 1.0f, 0.0f);    // ���E�̏����

    if ((float)WIN_WIDTH > (float)WIN_HEIGHT) {
        float zoom = (float)WIN_HEIGHT / 500;
        glScalef(zoom, zoom, zoom);
    }
    else {
        float zoom = (float)WIN_WIDTH / 500;
        glScalef(zoom, zoom, zoom);
    };

   
// �����̂̕`��
    glBegin(GL_TRIANGLES);
    for (int face = 0; face < 6; face++) {
        glColor3fv(colors[face]);
        for (int i = 0; i < 3; i++) {
            glVertex3fv(positions[indices[face * 2 + 0][i]]);
        }

        for (int i = 0; i < 3; i++) {
            glVertex3fv(positions[indices[face * 2 + 1][i]]);
        }
    }

    glEnd();
}

void resizeGL(GLFWwindow* window, int width, int height) {
    // ���[�U�Ǘ��̃E�B���h�E�T�C�Y��ύX
    WIN_WIDTH = width;
    WIN_HEIGHT = height;

    // GLFW�Ǘ��̃E�B���h�E�T�C�Y��ύX
    glfwSetWindowSize(window, WIN_WIDTH, WIN_HEIGHT);

    // ���ۂ̃E�B���h�E�T�C�Y (�s�N�Z����) ���擾
    int renderBufferWidth, renderBufferHeight;
    glfwGetFramebufferSize(window, &renderBufferWidth, &renderBufferHeight);

    // �r���[�|�[�g�ϊ��̍X�V
    glViewport(0, 0, renderBufferWidth, renderBufferHeight);
}

int main(int argc, char** argv) {
    // OpenGL������������
    if (glfwInit() == GL_FALSE) {
        fprintf(stderr, "Initialization failed!\n");
        return 1;
    }

    // Window�̍쐬
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Window creation failed!");
        glfwTerminate();
        return 1;
    }

    // OpenGL�̕`��Ώۂ�Window��ǉ�
    glfwMakeContextCurrent(window);

    // �E�B���h�E�̃��T�C�Y�������֐��̓o�^
    glfwSetWindowSizeCallback(window, resizeGL);

    // OpenGL��������
    initializeGL();

    // ���C�����[�v
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        // �`��
        paintGL();

        // �`��p�o�b�t�@�̐؂�ւ�
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
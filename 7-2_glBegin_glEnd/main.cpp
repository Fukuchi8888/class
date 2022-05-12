#include <cstdio>
#include <cmath>
#include <vector>


#define GLFW_INCLUDE_GLU  // GLU���C�u�������g�p����̂ɕK�v
#include <GLFW/glfw3.h>

static int WIN_WIDTH = 500;                       // �E�B���h�E�̕�
static int WIN_HEIGHT = 500;                       // �E�B���h�E�̍���
static const char* WIN_TITLE = "OpenGL Course";     // �E�B���h�E�̃^�C�g��


static const double PI = 4.0 * atan(1.0);           // �~�����̒�`



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

// �L���[�u�̕`��
void drawCube() {
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

// OpenGL�̕`��֐�
void paintGL1000() {
    // �w�i�F�Ɛ[�x�l�̃N���A
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ���W�̕ϊ�
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(75.0f, 40.0f, 125.0f,     // ���_�̈ʒu
        0.0f, 0.0f, 0.0f,     // ���Ă����
        0.0f, 1.0f, 0.0f);    // ���E�̏����

    for (float i = 0; i < 10; i += 1) {
        for (float ii = 0; ii < 10; ii += 1) {
            for (float iii = 0; iii < 10; iii += 1) {
                glPushMatrix();
                glTranslatef(i-5.0,ii-5.0,iii-5.0);
                glScalef(0.25f, 0.25f, 0.25f);

                drawCube();
                glPopMatrix();
            }
        }
    }


}


void paintGL1000000() {
    // �w�i�F�Ɛ[�x�l�̃N���A
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ���W�̕ϊ�
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(75.0f, 40.0f, 125.0f,     // ���_�̈ʒu
        0.0f, 0.0f, 0.0f,     // ���Ă����
        0.0f, 1.0f, 0.0f);    // ���E�̏����

    for (float i = 0; i < 100; i += 1) {
        for (float ii = 0; ii < 100; ii += 1) {
            for (float iii = 0; iii < 100; iii += 1) {
                glPushMatrix();
                glTranslatef(i - 50.0, ii - 50.0, iii - 50.0);
                glScalef(0.25f, 0.25f, 0.25f);

                drawCube();
                glPopMatrix();
            }
        }
    }


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

    double prevTime0 = glfwGetTime();

    // OpenGL������������
    if (glfwInit() == GL_FALSE) {
        fprintf(stderr, "Initialization failed!\n");
        return 1;
    }

    // Window�̍쐬
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE,
        NULL, NULL);
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
    double currentTime0 = glfwGetTime();
    double hajimarumade = currentTime0 - prevTime0;
    double prevTime = glfwGetTime();
    std::vector<float> time;
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        double currentTime = glfwGetTime();

        double keikajikan = currentTime - prevTime;
        time.push_back(keikajikan);

        // �`��
        paintGL1000();
        //paintGL1000000();

        // �`��p�o�b�t�@�̐؂�ւ�
        glfwSwapBuffers(window);
        glfwPollEvents();

        // �O��X�V���Ԃ̍X�V
        prevTime = currentTime;

    }
    std::size_t size = time.size();
    float sigma = 0;
    for (int i = 0; i < size; i++) {
        sigma += time[i];
    }
    float ave = sigma / size;
    printf("\n�n�܂�܂� = %f [s],\t�v�Z�� = %d [��],\t���� = %f [s]\n", hajimarumade, size, ave);
}
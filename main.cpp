#include <cstdio>
#include <cmath>

#define GLFW_INCLUDE_GLU  // GLU���C�u�������g�p����̂ɕK�v
#include <GLFW/glfw3.h>
#include <time.h>
static int WIN_WIDTH = 500;                       // �E�B���h�E�̕�
static int WIN_HEIGHT = 500;                       // �E�B���h�E�̍���
static const char* WIN_TITLE = "OpenGL Course";     // �E�B���h�E�̃^�C�g��
static const double fps = 30.0;                     // FPS

static const double PI = 4.0 * atan(1.0);           // �~�����̒�`

static float theta = 0.0f;

static const float positions[15][3] = {
    { -0.2f, -0.5f, -1.0f },
    { -0.2f,  3.5f, -1.0f },
    {  0.2f, -0.5f, -1.0f },
    {  0.2f,  3.5f, -1.0f },
    { -0.2f, -0.5f, -0.9f },
    { -0.2f,  1.5f, -0.9f },
    {  0.2f, -0.5f, -0.9f },
    {  0.2f,  1.5f, -0.9f },
    { -0.1f, -0.5f, -0.8f },
    { -0.1f,  3.5f, -0.8f },
    {  0.1f, -0.5f, -0.8f },
    {  0.1f,  3.5f, -0.8f },
    {  0.0f,  0.0f, -1.1f },
    {-0.01f,  4.0f, -1.1f },
    { 0.01f,  4.0f, -1.1f }
};


static const float colors[6][3] = {
    { 1.0f, 0.0f, 0.0f },  // ��
    { 0.0f, 1.0f, 0.0f },  // ��
    { 0.0f, 0.0f, 1.0f },  // ��
    { 1.0f, 1.0f, 0.0f },  // �C�G���[
    { 0.0f, 1.0f, 1.0f },  // �V�A��
    { 1.0f, 0.0f, 1.0f },  // �}�[���^
};

static const unsigned int indices[7][3] = {
    { 0, 1, 2 }, { 1, 2, 3 },
    { 4, 5, 6 }, { 5, 6, 7 },
    { 8, 9,10 }, { 9,10, 11},
    {12,13,14 } //{ 0, 4, 2 },
    //{ 0, 1, 6 }, { 0, 6, 3 },
    //{ 0, 2, 5 }, { 0, 5, 3 }
};

// OpenGL�̏������֐�
void initializeGL() {
    // �w�i�F�̐ݒ� (��)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // �[�x�e�X�g�̗L����
    glEnable(GL_DEPTH_TEST);
}

// �L���[�u�̕`��
void hunsin() {
    glBegin(GL_TRIANGLES);
    glColor3fv(colors[0]);
    for (int i = 0; i < 3; i++) {
       glVertex3fv(positions[indices[0][i]]);
    }

    for (int i = 0; i < 3; i++) {
       glVertex3fv(positions[indices[1][i]]);
    }
    glEnd();
}

void jisin() {
    glBegin(GL_TRIANGLES);
    glColor3fv(colors[1]);
    for (int i = 0; i < 3; i++) {
       glVertex3fv(positions[indices[2][i]]);
    }

    for (int i = 0; i < 3; i++) {
       glVertex3fv(positions[indices[3][i]]);
    }
    glEnd();
}

void byosin() {
    glBegin(GL_TRIANGLES);
    glColor3fv(colors[2]);
    for (int i = 0; i < 3; i++) {
       glVertex3fv(positions[indices[4][i]]);
    }
    for (int i = 0; i < 3; i++) {
       glVertex3fv(positions[indices[5][i]]);
    }
    glEnd();
}

void haikeini() {
    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.2f, 0.7f);
    for (int i = 0; i < 8000; i++) {
        float v1 = 0.001 * i - 4;
        float v2 = sqrt(16 - pow(v1, 2.0));
        glVertex3f(v1, -v2, -1.1f);
        glVertex3f(v1, v2, -1.1f);
        glVertex3f(v1 + 0.001, -v2, -1.1f);

        glVertex3f(v1 + 0.001, -v2, -1.1f);
        glVertex3f(v1 + 0.001, v2, -1.1f);
        glVertex3f(v1, v2, -1.1f);
    };

    glEnd();

}


// OpenGL�̕`��֐�
    void paintGL(float theta, float hour,float minute , float second) {

        // �w�i�F�Ɛ[�x�l�̃N���A
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ���W�̕ϊ�
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0f, 0.0f, 10.0f,     // ���_�̈ʒu
            0.0f, 0.0f, 0.0f,     // ���Ă����
            0.0f, 1.0f, 0.0f);    // ���E�̏����

        // ���j
        int ffps = (theta-second*30) / 1800;
        float rotatemin = 6.0 * (ffps - minute);
        glPushMatrix();
        glRotatef(rotatemin, 0.0f, 0.0f, 1.0f);

        hunsin();
        glPopMatrix();

        // ���j
        float rotatehour = -30 * (hour + minute / 60) + theta / 3600;
        glPushMatrix();
        glRotated(rotatehour, 0.0f, 0.0f, 1.0f);

        jisin();
        glPopMatrix();

        //�b�j
        int fffps = theta / 30;
        float rotatesec = 6.0 * (fffps - second);
        glPushMatrix();
        glRotatef(rotatesec, 0.0f, 0.0f, 1.0f);

        byosin();
        glPopMatrix();

   
        haikeini();
    };


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

// �A�j���[�V�����̂��߂̃A�b�v�f�[�g
void animate() {
    theta -= 1.0f;  // 1�x������]
}

int main(int argc, char** argv) {
    // OpenGL������������
    if (glfwInit() == GL_FALSE) {
        fprintf(stderr, "Initialization failed!\n");
        return 1;
    }

    //���Ԃ̎擾
    time_t timer;
    struct tm *t_st;
    time(&timer);
    t_st = localtime(&timer);
    float hour = t_st->tm_hour;
    float minute = t_st->tm_min;
    float second = t_st->tm_sec;

 
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
    double prevTime = glfwGetTime();
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        double currentTime = glfwGetTime();

        // �o�ߎ��Ԃ� 1 / FPS �ȏ�Ȃ�`�悷��
        if (currentTime - prevTime >= 1.0 / fps) {
            // �^�C�g����FPS��\��
            double realFps = 1.0 / (currentTime - prevTime);
            char winTitle[256];
            sprintf(winTitle, "%s (%.3f)", WIN_TITLE, realFps);
            glfwSetWindowTitle(window, winTitle);

            // �`��
            paintGL(theta, hour, minute, second);

            // �A�j���[�V����
            animate();

            // �`��p�o�b�t�@�̐؂�ւ�
            glfwSwapBuffers(window);
            glfwPollEvents();

            // �O��X�V���Ԃ̍X�V
            prevTime = currentTime;
        }
    }
}
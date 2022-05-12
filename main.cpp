#include <cstdio>
#include <cmath>
#include <string>

#define GLFW_INCLUDE_GLU  // GLU���C�u�������g�p����̂ɕK�v
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "GLFW/stb_image.h"

#include "common.h"

static int WIN_WIDTH = 500;                 // �E�B���h�E�̕�
static int WIN_HEIGHT = 500;                 // �E�B���h�E�̍���
static const char* WIN_TITLE = "OpenGL Course";     // �E�B���h�E�̃^�C�g��

static const double PI = 4.0 * atan(1.0);           // �~�����̒�`

static float theta = 0.0f;

static const std::string TEX_FILE0 = std::string(DATA_DIRECTORY) + "level0.png";
static const std::string TEX_FILE1 = std::string(DATA_DIRECTORY) + "level1.png";
static const std::string TEX_FILE2 = std::string(DATA_DIRECTORY) + "level2.png";
static const std::string TEX_FILE3 = std::string(DATA_DIRECTORY) + "level3.png";


static GLuint textureId = 0u;
static bool enableMipmap = true;

static const float positions[4][3] = {
    { -1.0f,  0.0f, -1.0f },
    {  1.0f,  0.0f, -1.0f },
    { -1.0f,  0.0f,  1.0f },
    {  1.0f,  0.0f,  1.0f },
};

static const float texcoords[4][2] = {
    {  0.0f,  0.0f },
    {  1.0f,  0.0f },
    {  0.0f,  1.0f },
    {  1.0f,  1.0f }
};

static const unsigned int indices[2][3] = {
    { 0, 1, 3 }, { 0, 3, 2 }
};

// OpenGL�̏������֐�
void initializeGL() {
    // �w�i�F�̐ݒ� (��)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // �[�x�e�X�g�̗L����
    glEnable(GL_DEPTH_TEST);

    // �e�N�X�`���̗L����
    glEnable(GL_TEXTURE_2D);

    

    // �e�N�X�`���̐����ƗL����
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);


    // �e�N�X�`���̐ݒ�
    int texWidth0, texHeight0, channels0;
    unsigned char* bytes0 = stbi_load(TEX_FILE0.c_str(), &texWidth0, &texHeight0, &channels0, STBI_rgb_alpha);
    if (!bytes0) {
        fprintf(stderr, "Failed to load image file: %s\n", TEX_FILE0.c_str());
        exit(1);
    }

    int texWidth1, texHeight1, channels1;
    unsigned char* bytes1 = stbi_load(TEX_FILE1.c_str(), &texWidth1, &texHeight1, &channels1, STBI_rgb_alpha);
    if (!bytes1) {
        fprintf(stderr, "Failed to load image file: %s\n", TEX_FILE1.c_str());
        exit(1);
    }

    int texWidth2, texHeight2, channels2;
    unsigned char* bytes2 = stbi_load(TEX_FILE2.c_str(), &texWidth2, &texHeight2, &channels2, STBI_rgb_alpha);
    if (!bytes2) {
        fprintf(stderr, "Failed to load image file: %s\n", TEX_FILE2.c_str());
        exit(1);
    }

    int texWidth3, texHeight3, channels3;
    unsigned char* bytes3 = stbi_load(TEX_FILE3.c_str(), &texWidth3, &texHeight3, &channels3, STBI_rgb_alpha);
    if (!bytes3) {
        fprintf(stderr, "Failed to load image file: %s\n", TEX_FILE3.c_str());
        exit(1);
    }

    // �P���ȃe�N�X�`���̓]��

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 256, 256,
        0, GL_RGBA, GL_UNSIGNED_BYTE, bytes0);

    glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 128, 128,
        0, GL_RGBA, GL_UNSIGNED_BYTE, bytes1);

    glTexImage2D(GL_TEXTURE_2D, 2, GL_RGBA8, 64, 64,
        0, GL_RGBA, GL_UNSIGNED_BYTE, bytes2);

    glTexImage2D(GL_TEXTURE_2D, 3, GL_RGBA8, 32, 32,
        0, GL_RGBA, GL_UNSIGNED_BYTE, bytes3);

    glTexImage2D(GL_TEXTURE_2D, 4, GL_RGBA8, 16, 16,
        0, GL_RGBA, GL_UNSIGNED_BYTE, bytes3);

    glTexImage2D(GL_TEXTURE_2D, 5, GL_RGBA8, 8, 8,
        0, GL_RGBA, GL_UNSIGNED_BYTE, bytes3);

    glTexImage2D(GL_TEXTURE_2D, 6, GL_RGBA8, 4, 4,
        0, GL_RGBA, GL_UNSIGNED_BYTE, bytes3);

    glTexImage2D(GL_TEXTURE_2D, 7, GL_RGBA8, 2, 2,
        0, GL_RGBA, GL_UNSIGNED_BYTE, bytes3);

    glTexImage2D(GL_TEXTURE_2D, 8, GL_RGBA8, 1, 1,
        0, GL_RGBA, GL_UNSIGNED_BYTE, bytes3);



    // �e�N�X�`���̉�f�l�Q�ƕ��@�̐ݒ� (MIP map����)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // �e�N�X�`�����E�̐܂�Ԃ��ݒ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // �e�N�X�`���̖�����
    glBindTexture(GL_TEXTURE_2D, 0);

    // ���[�h������f���̔j��
    stbi_image_free(bytes0);
    stbi_image_free(bytes1);
    stbi_image_free(bytes2);
    stbi_image_free(bytes3);
}

// OpenGL�̕`��֐�
void paintGL() {
    // �w�i�F�Ɛ[�x�l�̃N���A
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ���W�̕ϊ�
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 3.0f, 5.0f,     // ���_�̈ʒu
        0.0f, 0.0f, 0.0f,     // ���Ă����
        0.0f, 1.0f, 0.0f);    // ���E�̏����

    glTranslatef(0.0f, 0.0f, std::cos(PI * theta / 180.0f) * 4.0f - 2.0f); // �O������Ɉړ�
    glRotatef(theta, 0.0f, 1.0f, 0.0f);  // y�����S��theta������]

    // �����̂̕`��
    glBindTexture(GL_TEXTURE_2D, textureId);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glTexCoord2fv(texcoords[indices[0][i]]);
        glVertex3fv(positions[indices[0][i]]);
    }

    for (int i = 0; i < 3; i++) {
        glTexCoord2fv(texcoords[indices[1][i]]);
        glVertex3fv(positions[indices[1][i]]);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

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

// �A�j���[�V�����̂��߂̃A�b�v�f�[�g
void animate() {
    theta += 0.1f;  // 1�x������]
}

int main(int argc, char** argv) {
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
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        // �`��
        paintGL();

        // �A�j���[�V����
        animate();

        // �`��p�o�b�t�@�̐؂�ւ�
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
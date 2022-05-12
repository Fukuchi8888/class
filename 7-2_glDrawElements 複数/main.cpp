#include <cstdio>
#include <vector>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

static int WIN_WIDTH = 500;                       // �E�B���h�E�̕�
static int WIN_HEIGHT = 500;                       // �E�B���h�E�̍���
static const char* WIN_TITLE = "OpenGL Course nagai";     // �E�B���h�E�̃^�C�g��


// ���_�I�u�W�F�N�g
struct Vertex {
    Vertex(const glm::vec3& position_, const glm::vec3& color_)
        : position(position_)
        , color(color_) {
    }

    glm::vec3 position;
    glm::vec3 color;
};

static const glm::vec3 positions[8] = {
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f,  1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f,  1.0f),
    glm::vec3(1.0f,  1.0f, -1.0f),
    glm::vec3(-1.0f,  1.0f,  1.0f),
    glm::vec3(1.0f, -1.0f,  1.0f),
    glm::vec3(1.0f,  1.0f,  1.0f)
};

static const glm::vec3 colors[6] = {
    glm::vec3(1.0f, 0.0f, 0.0f),  // ��
    glm::vec3(0.0f, 1.0f, 0.0f),  // ��
    glm::vec3(0.0f, 0.0f, 1.0f),  // ��
    glm::vec3(1.0f, 1.0f, 0.0f),  // �C�G���[
    glm::vec3(0.0f, 1.0f, 1.0f),  // �V�A��
    glm::vec3(1.0f, 0.0f, 1.0f),  // �}�[���^
};

static const unsigned int faces[12][3] = {
    { 1, 6, 7 }, { 1, 7, 4 },
    { 2, 5, 7 }, { 2, 7, 4 },
    { 3, 5, 7 }, { 3, 7, 6 },
    { 0, 1, 4 }, { 0, 4, 2 },
    { 0, 1, 6 }, { 0, 6, 3 },
    { 0, 2, 5 }, { 0, 5, 3 }
};

// �o�b�t�@���Q�Ƃ���ԍ�
GLuint vertexBufferId;
GLuint indexBufferId;



// OpenGL�̏������֐�
void initializeGL() {
    // �[�x�e�X�g�̗L����
    glEnable(GL_DEPTH_TEST);

    // �w�i�F�̐ݒ� (��)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // ���_�z��̍쐬
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    int idx = 0;
    for (int face = 0; face < 6; face++) {
        for (int i = 0; i < 3; i++) {
            vertices.push_back(Vertex(positions[faces[face * 2 + 0][i]], colors[face]));
            indices.push_back(idx++);
        }

        for (int i = 0; i < 3; i++) {
            vertices.push_back(Vertex(positions[faces[face * 2 + 1][i]], colors[face]));
            indices.push_back(idx++);
        }
    }

    // ���_�o�b�t�@�̍쐬
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
        vertices.data(), GL_STATIC_DRAW);

    // ���_�ԍ��o�b�t�@�̍쐬
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(),
        indices.data(), GL_STATIC_DRAW);
}

// OpenGL�̕`��֐�
void paintGL1000() {
    // �w�i�F�̕`��
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

// ���_�o�b�t�@�̗L����
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));

    // �O�p�`�̕`��
    for (float i = 0; i < 10; i += 1) {
        for (float ii = 0; ii < 10; ii += 1) {
            for (float iii = 0; iii < 10; iii += 1) {
                glPushMatrix();
                glTranslatef(i - 5.0, ii - 5.0, iii - 5.0);
                glScalef(0.25f, 0.25f, 0.25f);

                
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                
                glPopMatrix();
            }
        }
    }
    

    // ���_�o�b�t�@�̖�����
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

}




void paintGL1000000() {
    // �w�i�F�̕`��
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

// ���_�o�b�t�@�̗L����
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));

    // �O�p�`�̕`��
    for (float i = 0; i < 100; i += 1) {
        for (float ii = 0; ii < 100; ii += 1) {
            for (float iii = 0; iii < 100; iii += 1) {
                glPushMatrix();
                glTranslatef(i - 50.0, ii - 50.0, iii - 50.0);
                glScalef(0.25f, 0.25f, 0.25f);
                


                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

                glPopMatrix();
            }
        }
    }


    // ���_�o�b�t�@�̖�����
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

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

    // OpenGL 3.x/4.x�̊֐������[�h���� (glfwMakeContextCurrent�̌�łȂ��Ƃ����Ȃ�)
    const int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        fprintf(stderr, "Failed to load OpenGL 3.x/4.x libraries!\n");
        return 1;
    }

    // �o�[�W�������o�͂���
    printf("Load OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    // OpenGL��������
    initializeGL();

    // �E�B���h�E�̃��T�C�Y�������֐��̓o�^
    glfwSetWindowSizeCallback(window, resizeGL);


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
        //paintGL1000();
        paintGL1000000();

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
    printf("\n����\t�n�܂�܂� = %f [s],\t�v�Z�� = %d [��],\t���� = %f [s]\n", hajimarumade, size, ave);
}
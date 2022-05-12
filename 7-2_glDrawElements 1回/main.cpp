#include <cstdio>
#include <vector>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

static int WIN_WIDTH = 500;                       // �E�B���h�E�̕�
static int WIN_HEIGHT = 500;                       // �E�B���h�E�̍���
static const char* WIN_TITLE = "OpenGL Course mijikai";     // �E�B���h�E�̃^�C�g��


// ���_�I�u�W�F�N�g
struct Vertex {
    Vertex(const glm::vec3& position_, const glm::vec3& color_)
        : position(position_)
        , color(color_) {
    }

    glm::vec3 position;
    glm::vec3 color;
};


static const glm::vec3 colors[6] = {
    glm::vec3(1.0f, 0.0f, 0.0f),  // ��
    glm::vec3(0.0f, 1.0f, 0.0f),  // ��
    glm::vec3(0.0f, 0.0f, 1.0f),  // ��
    glm::vec3(1.0f, 1.0f, 0.0f),  // �C�G���[
    glm::vec3(0.0f, 1.0f, 1.0f),  // �V�A��
    glm::vec3(1.0f, 0.0f, 1.0f),  // �}�[���^
};


// �o�b�t�@���Q�Ƃ���ԍ�
GLuint vertexBufferId;
GLuint indexBufferId;


// OpenGL�̏������֐�
void initializeGL1000() {

    static glm::vec3 positions[8000];
    static unsigned int faces[12000][3];

    // �[�x�e�X�g�̗L����
    glEnable(GL_DEPTH_TEST);

    // �w�i�F�̐ݒ� (��)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    int k = 0;
    for (int i = 0; i < 10; i++) {
        for (int ii = 0; ii < 10; ii++) {
            for (int iii = 0; iii < 10; iii++) {

                int p_0 = 0 + 8 * k;
                int p_1 = 1 + 8 * k;
                int p_2 = 2 + 8 * k;
                int p_3 = 3 + 8 * k;
                int p_4 = 4 + 8 * k;
                int p_5 = 5 + 8 * k;
                int p_6 = 6 + 8 * k;
                int p_7 = 7 + 8 * k;

                int f_0 = 0 + 12 * k;
                int f_1 = 1 + 12 * k;
                int f_2 = 2 + 12 * k;
                int f_3 = 3 + 12 * k;
                int f_4 = 4 + 12 * k;
                int f_5 = 5 + 12 * k;
                int f_6 = 6 + 12 * k;
                int f_7 = 7 + 12 * k;
                int f_8 = 8 + 12 * k;
                int f_9 = 9 + 12 * k;
                int f_10 = 10 + 12 * k;
                int f_11 = 11 + 12 * k;

                float i2 = i * 1.0;
                float ii2 = ii * 1.0;
                float iii2 = iii * 1.0;

                float v0 = 0.25 + i2 - 5.0;
                float v1 = -0.25 + i2 - 5.0;
                float v2 = 0.25 + ii2 - 5.0;
                float v3 = -0.25 + ii2 - 5.0;
                float v4 = 0.25 + iii2 - 5.0;
                float v5 = -0.25 + iii2 - 5.0;

                
                positions[p_0] = glm::vec3(v1, v3, v5);
                positions[p_1] = glm::vec3(v0, v3, v5);
                positions[p_2] = glm::vec3(v1, v2, v5);
                positions[p_3] = glm::vec3(v1, v3, v4);
                positions[p_4] = glm::vec3(v0, v2, v5);
                positions[p_5] = glm::vec3(v1, v2, v4);
                positions[p_6] = glm::vec3(v0, v3, v4);
                positions[p_7] = glm::vec3(v0, v2, v4);

                faces[f_0][0] = 1 + 8 * k;
                faces[f_0][1] = 6 + 8 * k;
                faces[f_0][2] = 7 + 8 * k;
                faces[f_1][0] = 1 + 8 * k;
                faces[f_1][1] = 7 + 8 * k;
                faces[f_1][2] = 4 + 8 * k;
                faces[f_2][0] = 2 + 8 * k;
                faces[f_2][1] = 5 + 8 * k;
                faces[f_2][2] = 7 + 8 * k;
                faces[f_3][0] = 2 + 8 * k;
                faces[f_3][1] = 7 + 8 * k;
                faces[f_3][2] = 4 + 8 * k;
                faces[f_4][0] = 3 + 8 * k;
                faces[f_4][1] = 5 + 8 * k;
                faces[f_4][2] = 7 + 8 * k;
                faces[f_5][0] = 3 + 8 * k;
                faces[f_5][1] = 7 + 8 * k;
                faces[f_5][2] = 6 + 8 * k;
                faces[f_6][0] = 0 + 8 * k;
                faces[f_6][1] = 1 + 8 * k;
                faces[f_6][2] = 4 + 8 * k;
                faces[f_7][0] = 0 + 8 * k;
                faces[f_7][1] = 4 + 8 * k;
                faces[f_7][2] = 2 + 8 * k;
                faces[f_8][0] = 0 + 8 * k;
                faces[f_8][1] = 1 + 8 * k;
                faces[f_8][2] = 6 + 8 * k;
                faces[f_9][0] = 0 + 8 * k;
                faces[f_9][1] = 6 + 8 * k;
                faces[f_9][2] = 3 + 8 * k;
                faces[f_10][0] = 0 + 8 * k;
                faces[f_10][1] = 2 + 8 * k;
                faces[f_10][2] = 5 + 8 * k;
                faces[f_11][0] = 0 + 8 * k;
                faces[f_11][1] = 5 + 8 * k;
                faces[f_11][2] = 3 + 8 * k;

                k++;
            }
        }
    }
   
    // ���_�z��̍쐬
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    int idx = 0;
    for (int face = 0; face < 6000; face++) {
        for (int i = 0; i < 3; i++) {
            vertices.push_back(Vertex(positions[faces[face * 2 + 0][i]], colors[face % 6]));
            indices.push_back(idx++);

        }

        for (int i = 0; i < 3; i++) {
            vertices.push_back(Vertex(positions[faces[face * 2 + 1][i]], colors[face % 6]));
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




void initializeGL1000000() {

    static glm::vec3 positions[8000000];
    static unsigned int faces[12000000][3];

    // �[�x�e�X�g�̗L����
    glEnable(GL_DEPTH_TEST);

    // �w�i�F�̐ݒ� (��)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    int k = 0;
    for (int i = 0; i < 100; i++) {
        for (int ii = 0; ii < 100; ii++) {
            for (int iii = 0; iii < 100; iii++) {

                int p_0 = 0 + 8 * k;
                int p_1 = 1 + 8 * k;
                int p_2 = 2 + 8 * k;
                int p_3 = 3 + 8 * k;
                int p_4 = 4 + 8 * k;
                int p_5 = 5 + 8 * k;
                int p_6 = 6 + 8 * k;
                int p_7 = 7 + 8 * k;

                int f_0 = 0 + 12 * k;
                int f_1 = 1 + 12 * k;
                int f_2 = 2 + 12 * k;
                int f_3 = 3 + 12 * k;
                int f_4 = 4 + 12 * k;
                int f_5 = 5 + 12 * k;
                int f_6 = 6 + 12 * k;
                int f_7 = 7 + 12 * k;
                int f_8 = 8 + 12 * k;
                int f_9 = 9 + 12 * k;
                int f_10 = 10 + 12 * k;
                int f_11 = 11 + 12 * k;

                float i2 = i * 1.0;
                float ii2 = ii * 1.0;
                float iii2 = iii * 1.0;

                float v0 = 0.25 + i2 - 50.0;
                float v1 = -0.25 + i2 - 50.0;
                float v2 = 0.25 + ii2 - 50.0;
                float v3 = -0.25 + ii2 - 50.0;
                float v4 = 0.25 + iii2 - 50.0;
                float v5 = -0.25 + iii2 - 50.0;


                positions[p_0] = glm::vec3(v1, v3, v5);
                positions[p_1] = glm::vec3(v0, v3, v5);
                positions[p_2] = glm::vec3(v1, v2, v5);
                positions[p_3] = glm::vec3(v1, v3, v4);
                positions[p_4] = glm::vec3(v0, v2, v5);
                positions[p_5] = glm::vec3(v1, v2, v4);
                positions[p_6] = glm::vec3(v0, v3, v4);
                positions[p_7] = glm::vec3(v0, v2, v4);

                faces[f_0][0] = 1 + 8 * k;
                faces[f_0][1] = 6 + 8 * k;
                faces[f_0][2] = 7 + 8 * k;
                faces[f_1][0] = 1 + 8 * k;
                faces[f_1][1] = 7 + 8 * k;
                faces[f_1][2] = 4 + 8 * k;
                faces[f_2][0] = 2 + 8 * k;
                faces[f_2][1] = 5 + 8 * k;
                faces[f_2][2] = 7 + 8 * k;
                faces[f_3][0] = 2 + 8 * k;
                faces[f_3][1] = 7 + 8 * k;
                faces[f_3][2] = 4 + 8 * k;
                faces[f_4][0] = 3 + 8 * k;
                faces[f_4][1] = 5 + 8 * k;
                faces[f_4][2] = 7 + 8 * k;
                faces[f_5][0] = 3 + 8 * k;
                faces[f_5][1] = 7 + 8 * k;
                faces[f_5][2] = 6 + 8 * k;
                faces[f_6][0] = 0 + 8 * k;
                faces[f_6][1] = 1 + 8 * k;
                faces[f_6][2] = 4 + 8 * k;
                faces[f_7][0] = 0 + 8 * k;
                faces[f_7][1] = 4 + 8 * k;
                faces[f_7][2] = 2 + 8 * k;
                faces[f_8][0] = 0 + 8 * k;
                faces[f_8][1] = 1 + 8 * k;
                faces[f_8][2] = 6 + 8 * k;
                faces[f_9][0] = 0 + 8 * k;
                faces[f_9][1] = 6 + 8 * k;
                faces[f_9][2] = 3 + 8 * k;
                faces[f_10][0] = 0 + 8 * k;
                faces[f_10][1] = 2 + 8 * k;
                faces[f_10][2] = 5 + 8 * k;
                faces[f_11][0] = 0 + 8 * k;
                faces[f_11][1] = 5 + 8 * k;
                faces[f_11][2] = 3 + 8 * k;

                k++;
            }
        }
    }

    // ���_�z��̍쐬
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    int idx = 0;
    for (int face = 0; face < 6000000; face++) {
        for (int i = 0; i < 3; i++) {
            vertices.push_back(Vertex(positions[faces[face * 2 + 0][i]], colors[face % 6]));
            indices.push_back(idx++);

        }

        for (int i = 0; i < 3; i++) {
            vertices.push_back(Vertex(positions[faces[face * 2 + 1][i]], colors[face % 6]));
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
void paintGL() {
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
   


    glDrawElements(GL_TRIANGLES, 36000, GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_TRIANGLES, 36000000, GL_UNSIGNED_INT, 0);//�������厖�@���_����36000�ɂ����炤�܂�������




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

    // OpenGL��������
    initializeGL1000();
    //initializeGL1000000();

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
        paintGL();

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
    printf("\n�Z��\t�n�܂�܂� = %f [s],\t�v�Z�� = %d [��],\t���� = %f [s]\n", hajimarumade, size, ave);
}
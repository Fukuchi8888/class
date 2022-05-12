#include <cstdio>
#include <vector>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

static int WIN_WIDTH = 500;                       // ウィンドウの幅
static int WIN_HEIGHT = 500;                       // ウィンドウの高さ
static const char* WIN_TITLE = "OpenGL Course mijikai";     // ウィンドウのタイトル


// 頂点オブジェクト
struct Vertex {
    Vertex(const glm::vec3& position_, const glm::vec3& color_)
        : position(position_)
        , color(color_) {
    }

    glm::vec3 position;
    glm::vec3 color;
};


static const glm::vec3 colors[6] = {
    glm::vec3(1.0f, 0.0f, 0.0f),  // 赤
    glm::vec3(0.0f, 1.0f, 0.0f),  // 緑
    glm::vec3(0.0f, 0.0f, 1.0f),  // 青
    glm::vec3(1.0f, 1.0f, 0.0f),  // イエロー
    glm::vec3(0.0f, 1.0f, 1.0f),  // シアン
    glm::vec3(1.0f, 0.0f, 1.0f),  // マゼンタ
};


// バッファを参照する番号
GLuint vertexBufferId;
GLuint indexBufferId;


// OpenGLの初期化関数
void initializeGL1000() {

    static glm::vec3 positions[8000];
    static unsigned int faces[12000][3];

    // 深度テストの有効化
    glEnable(GL_DEPTH_TEST);

    // 背景色の設定 (黒)
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
   
    // 頂点配列の作成
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
   
    // 頂点バッファの作成
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
        vertices.data(), GL_STATIC_DRAW);

    // 頂点番号バッファの作成
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(),
        indices.data(), GL_STATIC_DRAW);
}




void initializeGL1000000() {

    static glm::vec3 positions[8000000];
    static unsigned int faces[12000000][3];

    // 深度テストの有効化
    glEnable(GL_DEPTH_TEST);

    // 背景色の設定 (黒)
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

    // 頂点配列の作成
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

    // 頂点バッファの作成
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
        vertices.data(), GL_STATIC_DRAW);

    // 頂点番号バッファの作成
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(),
        indices.data(), GL_STATIC_DRAW);
}







// OpenGLの描画関数
void paintGL() {
    // 背景色の描画
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 座標の変換
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(75.0f, 40.0f, 125.0f,     // 視点の位置
        0.0f, 0.0f, 0.0f,     // 見ている先
        0.0f, 1.0f, 0.0f);    // 視界の上方向

// 頂点バッファの有効化
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));

    // 三角形の描画
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
   


    glDrawElements(GL_TRIANGLES, 36000, GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_TRIANGLES, 36000000, GL_UNSIGNED_INT, 0);//ここが大事　頂点数を36000にしたらうまくいった




    // 頂点バッファの無効化
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void resizeGL(GLFWwindow* window, int width, int height) {
    // ユーザ管理のウィンドウサイズを変更
    WIN_WIDTH = width;
    WIN_HEIGHT = height;

    // GLFW管理のウィンドウサイズを変更
    glfwSetWindowSize(window, WIN_WIDTH, WIN_HEIGHT);

    // 実際のウィンドウサイズ (ピクセル数) を取得
    int renderBufferWidth, renderBufferHeight;
    glfwGetFramebufferSize(window, &renderBufferWidth, &renderBufferHeight);

    // ビューポート変換の更新
    glViewport(0, 0, renderBufferWidth, renderBufferHeight);
}




int main(int argc, char** argv) {

    double prevTime0 = glfwGetTime();

    // OpenGLを初期化する
    if (glfwInit() == GL_FALSE) {
        fprintf(stderr, "Initialization failed!\n");
        return 1;
    }


    // Windowの作成
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE,
        NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Window creation failed!");
        glfwTerminate();
        return 1;
    }

    // OpenGLの描画対象にWindowを追加
    glfwMakeContextCurrent(window);

    // OpenGL 3.x/4.xの関数をロードする (glfwMakeContextCurrentの後でないといけない)
    const int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        fprintf(stderr, "Failed to load OpenGL 3.x/4.x libraries!\n");
        return 1;
    }

    // OpenGLを初期化
    initializeGL1000();
    //initializeGL1000000();

    // ウィンドウのリサイズを扱う関数の登録
    glfwSetWindowSizeCallback(window, resizeGL);

    
    // メインループ
    double currentTime0 = glfwGetTime();
    double hajimarumade = currentTime0 - prevTime0;
    double prevTime = glfwGetTime();
    std::vector<float> time;
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        double currentTime = glfwGetTime();

        double keikajikan = currentTime - prevTime;
        time.push_back(keikajikan);

        // 描画
        paintGL();

        // 描画用バッファの切り替え
        glfwSwapBuffers(window);
        glfwPollEvents();

        // 前回更新時間の更新
        prevTime = currentTime;

    }
    std::size_t size = time.size();
    float sigma = 0;
    for (int i = 0; i < size; i++) {
        sigma += time[i];
    }
    float ave = sigma / size;
    printf("\n短い\t始まるまで = %f [s],\t計算数 = %d [回],\t平均 = %f [s]\n", hajimarumade, size, ave);
}
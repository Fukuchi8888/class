#include <cstdio>
#include <cmath>

#define GLFW_INCLUDE_GLU  // GLUライブラリを使用するのに必要
#include <GLFW/glfw3.h>
#include <time.h>
static int WIN_WIDTH = 500;                       // ウィンドウの幅
static int WIN_HEIGHT = 500;                       // ウィンドウの高さ
static const char* WIN_TITLE = "OpenGL Course";     // ウィンドウのタイトル
static const double fps = 30.0;                     // FPS

static const double PI = 4.0 * atan(1.0);           // 円周率の定義

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
    { 1.0f, 0.0f, 0.0f },  // 赤
    { 0.0f, 1.0f, 0.0f },  // 緑
    { 0.0f, 0.0f, 1.0f },  // 青
    { 1.0f, 1.0f, 0.0f },  // イエロー
    { 0.0f, 1.0f, 1.0f },  // シアン
    { 1.0f, 0.0f, 1.0f },  // マゼンタ
};

static const unsigned int indices[7][3] = {
    { 0, 1, 2 }, { 1, 2, 3 },
    { 4, 5, 6 }, { 5, 6, 7 },
    { 8, 9,10 }, { 9,10, 11},
    {12,13,14 } //{ 0, 4, 2 },
    //{ 0, 1, 6 }, { 0, 6, 3 },
    //{ 0, 2, 5 }, { 0, 5, 3 }
};

// OpenGLの初期化関数
void initializeGL() {
    // 背景色の設定 (黒)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // 深度テストの有効化
    glEnable(GL_DEPTH_TEST);
}

// キューブの描画
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


// OpenGLの描画関数
    void paintGL(float theta, float hour,float minute , float second) {

        // 背景色と深度値のクリア
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 座標の変換
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0f, 0.0f, 10.0f,     // 視点の位置
            0.0f, 0.0f, 0.0f,     // 見ている先
            0.0f, 1.0f, 0.0f);    // 視界の上方向

        // 分針
        int ffps = (theta-second*30) / 1800;
        float rotatemin = 6.0 * (ffps - minute);
        glPushMatrix();
        glRotatef(rotatemin, 0.0f, 0.0f, 1.0f);

        hunsin();
        glPopMatrix();

        // 時針
        float rotatehour = -30 * (hour + minute / 60) + theta / 3600;
        glPushMatrix();
        glRotated(rotatehour, 0.0f, 0.0f, 1.0f);

        jisin();
        glPopMatrix();

        //秒針
        int fffps = theta / 30;
        float rotatesec = 6.0 * (fffps - second);
        glPushMatrix();
        glRotatef(rotatesec, 0.0f, 0.0f, 1.0f);

        byosin();
        glPopMatrix();

   
        haikeini();
    };


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

// アニメーションのためのアップデート
void animate() {
    theta -= 1.0f;  // 1度だけ回転
}

int main(int argc, char** argv) {
    // OpenGLを初期化する
    if (glfwInit() == GL_FALSE) {
        fprintf(stderr, "Initialization failed!\n");
        return 1;
    }

    //時間の取得
    time_t timer;
    struct tm *t_st;
    time(&timer);
    t_st = localtime(&timer);
    float hour = t_st->tm_hour;
    float minute = t_st->tm_min;
    float second = t_st->tm_sec;

 
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

    // ウィンドウのリサイズを扱う関数の登録
    glfwSetWindowSizeCallback(window, resizeGL);

    // OpenGLを初期化
    initializeGL();

    // メインループ
    double prevTime = glfwGetTime();
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        double currentTime = glfwGetTime();

        // 経過時間が 1 / FPS 以上なら描画する
        if (currentTime - prevTime >= 1.0 / fps) {
            // タイトルにFPSを表示
            double realFps = 1.0 / (currentTime - prevTime);
            char winTitle[256];
            sprintf(winTitle, "%s (%.3f)", WIN_TITLE, realFps);
            glfwSetWindowTitle(window, winTitle);

            // 描画
            paintGL(theta, hour, minute, second);

            // アニメーション
            animate();

            // 描画用バッファの切り替え
            glfwSwapBuffers(window);
            glfwPollEvents();

            // 前回更新時間の更新
            prevTime = currentTime;
        }
    }
}

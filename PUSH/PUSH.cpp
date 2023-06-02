﻿// PUSH.cpp : définit le point d'entrée de l'application.
//

#include "PUSH.h"

using namespace std;
namespace fs = std::filesystem;
using namespace glm;

GLFWwindow* window;


///////////////////////////////////////////////////////////////////////////////
//
// 
//      Fonctions

void mouvForm(Piece& pPiece, const double xCursor, const double yCursor) {
    pPiece.x0 = xCursor; // D�placement horizontal
    pPiece.y0 = yCursor; // D�placement vertical

    pPiece.createPoint(); // Permet de changer tout les points
}

void drawTriangle(vector<vector<float>> pPointXY, vector<vector<float>> pContourXY) {
    // Permet de dessiner des triangles
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < pPointXY[0].size(); i++)
    {
        glColor3f(0.569f, 0.545f, 0.545f); // Couleur de la piece
        glVertex2f(pPointXY[0][i], pPointXY[1][i]);
    }
    glEnd();

    // Permet de dessiner les contours
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < pContourXY[0].size(); i++)
    {
        glColor3f(1.0f, 0.0f, 0.0f); // Rouge
        glVertex2f(pContourXY[0][i], pContourXY[1][i]);
    }
    glEnd();
}

void PositionCursor(GLFWwindow* pWindow, double& xCursor, double& yCursor, const int width, const int height)
{
    double xpos;
    double ypos;
    glfwGetCursorPos(pWindow, &xpos, &ypos);

    if (xpos < 0)
    {
        xpos = xpos / 11;
    }
    else if (xpos > 0)
    {
        xpos = xpos / (width - 11);
    }

    if (ypos < 0)
    {
        ypos = (ypos / 11);
    }
    if (ypos > 0)
    {
        ypos = (ypos / (height - 11));
    }

    xCursor = (xpos - 0.5) * 2;
    yCursor = -(ypos - 0.5) * 2;
}


void createPiece(GLFWwindow* pWindow, vector <Piece>& pPieceArray)//, bool& pProcessMove) 
{
    Piece newProcessus = Piece(Type::Processus);
    Piece newIn = Piece(Type::In);
    Piece newOut = Piece(Type::Out);
    Piece newError = Piece(Type::Error);
    Piece newTube = Piece(Type::Tube);

    /*
    static int oldState = GLFW_RELEASE;//0
    int newState = glfwGetKey(window, GLFW_KEY_ENTER);// 1 if pressed
    if (newState == GLFW_RELEASE && oldState == GLFW_PRESS)
    {
        pPieceArray.insert(pPieceArray.end(), newProcessus);
    }
    oldState = newState;
    */


    static int oldStateProcessus = GLFW_RELEASE; //0
    static int oldStateIn = GLFW_RELEASE; //0
    static int oldStateOut = GLFW_RELEASE; //0
    static int oldStateError = GLFW_RELEASE; //0
    static int oldStateTube = GLFW_RELEASE; //0

    int newStateProcessus = glfwGetKey(window, GLFW_KEY_P); // 1 if pressed
    if (newStateProcessus == GLFW_RELEASE && oldStateProcessus == GLFW_PRESS)
    {
        pPieceArray.insert(pPieceArray.end(), newProcessus);
    }
    oldStateProcessus = newStateProcessus;

    int newStateIn = glfwGetKey(window, GLFW_KEY_I);
    if (newStateIn == GLFW_RELEASE && oldStateIn == GLFW_PRESS)
    {
        pPieceArray.insert(pPieceArray.end(), newIn);
    }
    oldStateIn = newStateIn;

    int newStateOut = glfwGetKey(window, GLFW_KEY_O);
    if (newStateOut == GLFW_RELEASE && oldStateOut == GLFW_PRESS)
    {
        pPieceArray.insert(pPieceArray.end(), newOut);
    }
    oldStateOut = newStateOut;

    int newStateError = glfwGetKey(window, GLFW_KEY_E);
    if (newStateError == GLFW_RELEASE && oldStateError == GLFW_PRESS)
    {
        pPieceArray.insert(pPieceArray.end(), newError);
    }
    oldStateError = newStateError;

    int newStateTube = glfwGetKey(window, GLFW_KEY_T);
    if (newStateTube == GLFW_RELEASE && oldStateTube == GLFW_PRESS)
    {
        pPieceArray.insert(pPieceArray.end(), newTube);
    }
    oldStateTube = newStateTube;
}

void updatePiecePosition(GLFWwindow* window, const double& xCursor, const double& yCursor, vector <Piece>& pPieceArray)
{
    for (int i = 0; i < pPieceArray.size(); i++)
    {
        if (pPieceArray[i].isPointInsideForm(xCursor, yCursor))
        {
            mouvForm(pPieceArray[i], xCursor, yCursor);
            return; // Permet de selectionner une seule piece
        }
    }
}

void supressPiece(GLFWwindow* window, const double& xCursor, const double& yCursor, vector <Piece>& pPieceArray)
{
    for (int i = 0; i < pPieceArray.size(); i++)
    {
        if (pPieceArray[i].isPointInsideForm(xCursor, yCursor))
        {
            pPieceArray.erase(pPieceArray.begin() + i);
        }
    }
}

void drawPiece(vector <Piece> pPieceArray)
{
    for (int i = 0; i < pPieceArray.size(); i++)
    {
        drawTriangle(pPieceArray[i].pointXY, pPieceArray[i].contourXY);
    }
}

void cd(const string& pCommand, string& pPath) {
    string vStartPath = pPath;
    int vEnd = pCommand.size();
    int StartWord = 0;
    char c[100];
    for (int i = 0; i < pCommand.size(); i++) {
        if (pCommand[i] == '/' || i+1 == pCommand.size() || pCommand[i] == ' ') {
            string vCommand = pCommand.substr(StartWord, i + 1 - StartWord);
            if (pPath == "."&& vCommand.substr(0,2) == "..") {
                StartWord = i + 1;
                return;
            }
            int Error = chdir(vCommand.c_str());
            if (Error == -1) {
                chdir(getcwd(c, 100));
                pPath = vStartPath;
                return;
            }
            StartWord = i+1;
            string vPath = getcwd(c, 100);
            int vPush = vPath.rfind("PUSH");
            pPath = "." + vPath.substr(vPush + 16, vPath.size() - vPush);
        }
        if (pCommand[i] == ' ') return;
    }
}

//my_popen allow us to get the output of a command(string) in a vector of string
//Only right commands will give a result
//Other will give an empty line

void my_popen(const string& pCommand, vector<string>& pOutput, string& pPath) {
    FILE* vFile;
    const int vSizeBuf = 1234;
    char vBuff[vSizeBuf];
    pOutput = vector<string>();
    char c[100];
    string vPath = "cd " + string(getcwd(c,100)) + " && " + pCommand;
    if ((vFile = popen(vPath.c_str(), "r")) == NULL)
    {
        cout << "error, File NULL" << endl;
    }

    string vCurrent_string = "";

    while (fgets(vBuff, sizeof(vBuff), vFile))
    {
        vCurrent_string += vBuff;
    }

    pOutput.push_back(vCurrent_string.substr(0, vCurrent_string.size() - 1));
    if (pCommand.substr(0, 2) == "cd") {
        cd(pCommand.substr(3, pCommand.size() - 3), pPath);
    }
    pclose(vFile);
}//Code from stackoverflow

void init(string& pPath) {
    vector<string> vOutput;
    const auto vWorkingDir = fs::current_path();
    if(!fs::is_directory(vWorkingDir / "Environment"))
        my_popen("mkdir Environment", vOutput, pPath);
    my_popen("cd Environment", vOutput, pPath);
}


int main()
{
    //LOL
	cout << "Hello CMake." << endl;
    string path = ".";
    init(path);
    //cout << current_path.back() << "\n";
    //We have a command
    string vCommand = "cd test/test2";
    //We save the result of the command in output
    vector<string> vOutput;
    my_popen(vCommand, vOutput, path);
    //We check if the output has the good values
    for (vector<string>::iterator vIterator = vOutput.begin(); vIterator != vOutput.end(); ++vIterator)
    {
       cout << *vIterator << endl;
    }//It has
    vCommand = "cd ../../test";
    my_popen(vCommand, vOutput, path);
    char c[100];

    //GLFWwindow* window;
    //bool processusMove = false;

    //taille de la fenetre
    int windowWidth = 1900;
    int windowHeight = 1060;

    //intialisation de la position du curseur, 
    double xCursor = 0;
    double yCursor = 0;

    // Initialisation de GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Cr�ation de la fen�tre
    window = glfwCreateWindow(windowWidth, windowHeight, "PUSH", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    //Vraie valeur de la position du curseur
    PositionCursor(window, xCursor, yCursor, windowWidth, windowHeight);

    // Configuration de GLFW
    glfwMakeContextCurrent(window);

    // Colorisation
    glClearColor(0.969f, 0.941f, 0.941f, 0.0f);

    // Cr�e les pi�ces
    vector <Piece> pieceArray;

    //Processus forme = Processus();


    // Boucle principale
    while ((glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)) {

        //met a jour la valeur de la position du curseur
        PositionCursor(window, xCursor, yCursor, windowWidth, windowHeight);

        createPiece(window, pieceArray);

        // Effacer le contenu de la fen�tre
        glClear(GL_COLOR_BUFFER_BIT);

        // Mise � jour des pieces
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) //regarde si le bouton gauche est appuye
        {
            updatePiecePosition(window, xCursor, yCursor, pieceArray);
        }
        // Suppression des pieces
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) //regarde si le bouton droit est appuye
        {
            supressPiece(window, xCursor, yCursor, pieceArray);
        }

        // Dessiner les pieces
        drawPiece(pieceArray);

        // �change des tampons d'affichage
        glfwSwapBuffers(window);

        // V�rification des �v�nements de la fen�tre
        glfwPollEvents();
    }

    // Terminaison de GLFW
    glfwTerminate();
    return 0;
}

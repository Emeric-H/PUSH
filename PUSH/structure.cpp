// Include STD
#include <iostream>
#include <vector>
using namespace std;


///////////////////////////////////////////////////////////////////////////////
//
// 
//      Structures et Enum

struct Zone
{
	// attributes of BOTTOM LEFT corner's position
	float aPosX;
	float aPosY;

	// Length and height attributes
	float aLength;
	float aHeight;

	// List of corners' coordinates
	vector<vector<float>> aCornersList;

	// Constructors
	Zone(float pPosX, float pPosY, float pLength, float pHeight)
	{
		aPosX = pPosX;
		aPosY = pPosY;
		aLength = pLength;
		aHeight = pHeight;
		createCornersList();
	}

	Zone() {}

	// 
	void createCornersList()
	{
		float cornerBLX = aPosX;
		float cornerBLY = aPosY;
		float cornerTLX = aPosX;
		float cornerTLY = aPosY + aHeight;
		float cornerTRX = aPosX + aLength;
		float cornerTRY = aPosY + aHeight;
		float cornerBRX = aPosX + aLength;
		float cornerBRY = aPosY;

		aCornersList = { {cornerBLX, cornerTLX, cornerTRX, cornerBRX},
						 {cornerBLY, cornerTLY, cornerTRY, cornerBRY} };
	}

};

struct Button : public Zone
{
	string aText;

	// Constructors
	Button(float pPosX, float pPosY, string pText) : Zone(pPosX, pPosY, 0.2, 0.1)
	{
		aText = pText;
	}

	Button() {}

	bool buttonPressed(float pXCursor, float pYCursor)
	{
		if (pXCursor > aPosX && pXCursor < aPosX + aLength && pYCursor > aPosY && pYCursor < aPosY + aHeight)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct Piece
{

	// Données pour la Pièce
	float x0 = 0.0;
	float x1, x2, x3, x4, x5;

	float y0 = 0.0;
	float y1, y2, y3, y4, y5;

	vector <vector<float>> pointXY;
	vector <vector<float>> contourXY;

	string text = "";

	// Constructeur
	Piece() {}

	virtual void createPoint() {}

	bool isPointInsideForm(const float xCursor, const float yCursor) {
		// Coordonnées des sommets du triangle
		for (int i = 0; i < pointXY[0].size() - 2; i = i + 3) {
			float x1 = pointXY[0][i];
			float x2 = pointXY[0][i + 1];
			float x3 = pointXY[0][i + 2];
			float y1 = pointXY[1][i];
			float y2 = pointXY[1][i + 1];
			float y3 = pointXY[1][i + 2];

			// Calcul des barycentres
			float denom = ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
			float b1 = ((y2 - y3) * (xCursor - x3) + (x3 - x2) * (yCursor - y3)) / denom;
			float b2 = ((y3 - y1) * (xCursor - x3) + (x1 - x3) * (yCursor - y3)) / denom;
			float b3 = 1.0f - b1 - b2;

			// Vérification si le point est à l'intérieur du triangle
			if ((b1 >= 0.0f) && (b2 >= 0.0f) && (b3 >= 0.0f)) return true;
		}
		return false;
	}

};

struct Processus : public Piece
{
	bool inProcessus = true, outProcessus = true, errorProcessus = true;

	Processus() 
	{ 
		createPoint();
		text = "ls -l";

	}

	void createPoint() override {
		x1 = x0 - 0.05;
		x2 = x0 + 0.05;
		x3 = x0 - 0.03;
		x4 = x0 + 0.03;
		x5 = x0 + 0.07;

		y1 = y0 - 0.05;
		y2 = y0 + 0.05;
		y3 = y0 - 0.03;
		y4 = y0 + 0.03;
		y5 = y0 - 0.07;

		pointXY = { { x1, x2, x2, x1, x1, x2, x1, x1, x2, x1, x2, x2, x3, x2, x2, x3, x3, x2, x2, x2, x5, x3, x4, x0 },
					{ y2, y2, y4, y2, y4, y4, y1, y3, y3, y1, y1, y3, y2, y2, y1, y2, y1, y1, y4, y3, y0, y1, y1, y5 } };
		contourXY = { { x1, x2, x2, x5, x2, x2, x4, x0, x3, x1, x1, x3, x3, x1 },
					{ y2, y2, y4, y0, y3, y1, y1, y5, y1, y1, y3, y3, y4, y4 } };
	}

};


struct In : public Piece
{
	bool outIn = true;

	In() { createPoint(); }

	void createPoint() {
		x1 = x0 - 0.05;
		x2 = x0 + 0.05;
		x3 = x0 - 0.03;
		x4 = x0 + 0.03;
		x5 = x0 + 0.07;

		y1 = y0 - 0.05;
		y2 = y0 + 0.05;
		y3 = y0 - 0.03;
		y4 = y0 + 0.03;
		y5 = y0 - 0.07;

		pointXY = { { x1, x2, x2, x1, x1, x2, x2, x2, x5, x5, x2, x5 },
					{ y2, y2, y1, y2, y1, y1, y4, y3, y4, y4, y3, y3 } };
		contourXY = { { x1, x2, x2, x5, x5, x2, x2, x1 },
					{ y2, y2, y4, y4, y3, y3, y1, y1 } };
	}

};


struct Out : public Piece
{
	bool inOut = true;

	Out() { createPoint(); }

	void createPoint() {
		x1 = x0 - 0.05;
		x2 = x0 + 0.05;
		x3 = x0 - 0.03;
		x4 = x0 + 0.03;
		x5 = x0 + 0.07;

		y1 = y0 - 0.05;
		y2 = y0 + 0.05;
		y3 = y0 - 0.03;
		y4 = y0 + 0.03;
		y5 = y0 - 0.07;

		pointXY = { { x1, x2, x2, x1, x1, x2, x1, x2, x1, x1, x2, x2, x3, x2, x2, x3, x2, x3, x1, x3, x3, x1, x3, x3 },
					{ y1, y3, y1, y3, y1, y3, y2, y2, y4, y4, y2, y4, y2, y2, y1, y2, y1, y1, y4, y4, y0, y3, y3, y0 } };
		contourXY = { { x1, x2, x2, x1, x1, x3, x1 },
					{ y2, y2, y1, y1, y3, y0, y4 } };
	}

};


struct Error : public Piece
{
	bool inError = true;

	Error() { createPoint(); }

	void createPoint() {
		x1 = x0 - 0.05;
		x2 = x0 + 0.05;
		x3 = x0 - 0.03;
		x4 = x0 + 0.03;
		x5 = x0 + 0.07;

		y1 = y0 - 0.05;
		y2 = y0 + 0.05;
		y3 = y0 - 0.03;
		y4 = y0 + 0.03;
		y5 = y0 - 0.07;

		pointXY = { { x1, x1, x3, x1, x3, x3, x2, x2, x4, x2, x4, x4, x1, x2, x1, x2, x2, x1, x4, x0, x4, x3, x0, x3 },
					{ y1, y2, y2, y1, y2, y1, y2, y1, y1, y2, y2, y1, y1, y1, y4, y4, y1, y4, y2, y4, y4, y2, y4, y4 } };
		contourXY = { { x1, x3, x0, x4, x2, x2, x1 },
					{ y2, y2, y4, y2, y2, y1, y1 } };
	}

};

struct Tube : public Piece
{
	bool inTube = true, outTube = true;

	Tube()
	{
		createPoint();
		text = " | ";
	}

	void createPoint() override {
		x1 = x0 - 0.05;
		x2 = x0 + 0.05;
		x3 = x0 - 0.03;
		x4 = x0 + 0.03;
		x5 = x0 + 0.07;

		y1 = y0 - 0.05;
		y2 = y0 + 0.05;
		y3 = y0 - 0.03;
		y4 = y0 + 0.03;
		y5 = y0 - 0.07;

		pointXY = { { x1, x2, x2, x1, x1, x2, x1, x1, x2, x1, x2, x2, x2, x2, x3, x3, x2, x3, x1, x3, x3, x1, x3, x3, x2, x2, x5, x5, x2, x5 },
					{ y2, y2, y4, y2, y4, y4, y1, y3, y3, y1, y1, y3, y4, y3, y4, y3, y3, y4, y3, y0, y3, y4, y0, y4, y4, y3, y4, y4, y3, y3 } };
		contourXY = { { x1, x2, x2, x5, x5, x2, x2, x1, x1, x3, x1 },
					{ y2, y2, y4, y4, y3, y3, y1, y1, y3, y0, y4 } };
	}

};
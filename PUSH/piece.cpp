// Include STD
#include <iostream>
#include <vector>
using namespace std;


///////////////////////////////////////////////////////////////////////////////
//
// 
//      Structures et Enum

enum class Type { Processus, In, Out, Error, Tube };

struct Piece {

	// Donn�es pour la Piece
	float x0 = 0.0;
	float x1, x2, x3, x4, x5;

	float y0 = 0.0;
	float y1, y2, y3, y4, y5;

	vector <vector<float>> pointXY;
	vector <vector<float>> contourXY;

	Type type;

	// Constructeur
	Piece(Type pType) {
		type = pType;
		createPoint();
	}

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

		if (type == Type::Processus)
		{
			pointXY = { { x1, x2, x2, x1, x1, x2, x1, x1, x2, x1, x2, x2, x3, x2, x2, x3, x3, x2, x2, x2, x5, x3, x4, x0 },
						{ y2, y2, y4, y2, y4, y4, y1, y3, y3, y1, y1, y3, y2, y2, y1, y2, y1, y1, y4, y3, y0, y1, y1, y5 } };
			contourXY = { { x1, x2, x2, x5, x5, x2, x2, x1, x1},
						  { y2, y2, y4, y4, y3, y3, y1, y1, y2} };
		}
		if (type == Type::In)
		{
			pointXY = { { x1, x2, x2, x1, x1, x2, x2, x2, x5, x5, x2, x5 },
						{ y2, y2, y1, y2, y1, y1, y4, y3, y4, y4, y3, y3 } };
			contourXY = { { x1, x2, x2, x5, x5, x2, x2, x1, x1},
						  { y2, y2, y4, y4, y3, y3, y1, y1, y2} };
		}
		if (type == Type::Out)
		{
			pointXY = { { x1, x2, x2, x1, x1, x2, x1, x2, x1, x1, x2, x2, x3, x2, x2, x3, x2, x3, x1, x3, x3, x1, x3, x3 },
						{ y1, y3, y1, y3, y1, y3, y2, y2, y4, y4, y2, y4, y2, y2, y1, y2, y1, y1, y4, y4, y0, y3, y3, y0 } };
			contourXY = { { x1, x2, x2, x5, x5, x2, x2, x1, x1},
						  { y2, y2, y4, y4, y3, y3, y1, y1, y2} };
		}
		if (type == Type::Error)
		{
			pointXY = { { x1, x1, x3, x1, x3, x3, x2, x2, x4, x2, x4, x4, x1, x2, x1, x2, x2, x1, x4, x0, x4, x3, x0, x3 },
						{ y1, y2, y2, y1, y2, y1, y2, y1, y1, y2, y2, y1, y1, y1, y4, y4, y1, y4, y2, y4, y4, y2, y4, y4 } };
			contourXY = { { x1, x2, x2, x5, x5, x2, x2, x1, x1},
						  { y2, y2, y4, y4, y3, y3, y1, y1, y2} };
		}
		if (type == Type::Tube)
		{
			pointXY = { { x1, x2, x2, x1, x1, x2, x1, x1, x2, x1, x2, x2, x2, x2, x3, x3, x2, x3, x1, x3, x3, x1, x3, x3, x2, x2, x5, x5, x2, x5 },
						{ y2, y2, y4, y2, y4, y4, y1, y3, y3, y1, y1, y3, y4, y3, y4, y3, y3, y4, y3, y0, y3, y4, y0, y4, y4, y3, y4, y4, y3, y3 } };
			contourXY = { { x1, x2, x2, x5, x5, x2, x2, x1, x1},
						  { y2, y2, y4, y4, y3, y3, y1, y1, y2} };
		}
	}

	bool isPointInsideForm(const double xCursor, const double yCursor) {
		// Coordonn�es des sommets du triangle
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

			// V�rification si le point est � l'int�rieur du triangle
			if ((b1 >= 0.0f) && (b2 >= 0.0f) && (b3 >= 0.0f)) return true;
		}
		return false;
	}

};
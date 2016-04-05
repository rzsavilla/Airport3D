#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D() {
	m_fData[0] = 0.0f;
	m_fData[1] = 0.0f;
	m_fData[2] = 0.0f;
	init();
}

Vector3D::Vector3D(float x, float y, float z) {
	m_fData[0] = x;
	m_fData[1] = y;
	m_fData[2] = z;
	init();
}

void Vector3D::init() {
	m_bHasMagnitude = false;
}

void Vector3D::setX(float x) {
	m_fData[0] = x;
	m_bHasMagnitude = false;		//Magnitude need to be re-calculated
}
void Vector3D::setY(float y) {
	m_fData[1] = y;
	m_bHasMagnitude = false;		//Magnitude need to be re-calculated
}
void Vector3D::setZ(float z) {
	m_fData[2] = z;
	m_bHasMagnitude = false;		//Magnitude need to be re-calculated
}

float Vector3D::getX(){
	return m_fData[0];		//Return x element
}
float Vector3D::getY(){
	return m_fData[1];		//Return y element
}
float Vector3D::getZ(){
	return m_fData[2];		//Return z element
}

float Vector3D::angle(Vector3D& other) {
	//acos(theta) = a.b / |a||b|
	return acos(this->dotProduct(other) / (this->magnitude() * other.magnitude()));
}		
float Vector3D::dotProduct(const Vector3D& other){
	//(ax * bx) + (ay * by) + (az * by)
	return (this->m_fData[0] * other.m_fData[0]) + (this->m_fData[1] * other.m_fData[1]) + (this->m_fData[2] * other.m_fData[2]);
}
float Vector3D::magnitude() {
	if (!m_bHasMagnitude) {
		//Calculate and store magnitude
		m_fMagnitude = sqrt((m_fData[0] * m_fData[0] + m_fData[1] * m_fData[1] + m_fData[2] * m_fData[2]));
		m_bHasMagnitude = true;
	}
	return m_fMagnitude;
}

Vector3D Vector3D::unitVector(){
	// a / |a|
	//Each element is divided by the vectors magnitude
	return Vector3D(m_fData[0] / this->magnitude(), m_fData[1] / this->magnitude(), m_fData[2] / this->magnitude());
}						
Vector3D Vector3D::crossProduct(const Vector3D& other){
	/* A x B = 
		(ay * bz - az * by)x
		(az * bx - ax * bz)y
		(ax * by - ay * bx)z
	*/
	float x = (this->m_fData[1] * other.m_fData[2]) - (this->m_fData[2] * other.m_fData[1]);
	float y = (this->m_fData[2] * other.m_fData[0]) - (this->m_fData[0] * other.m_fData[2]);
	float z = (this->m_fData[0] * other.m_fData[1]) - (this->m_fData[1] * other.m_fData[0]);
	return Vector3D(x,y,z);
}

Vector3D Vector3D::operator+ (const Vector3D& other){
	return Vector3D(
		this->m_fData[0] + other.m_fData[0],
		this->m_fData[1] + other.m_fData[1],
		this->m_fData[2] + other.m_fData[2]
		);
}
Vector3D Vector3D::operator- (const Vector3D& other){
	return Vector3D(
		this->m_fData[0] - other.m_fData[0],
		this->m_fData[1] - other.m_fData[1],
		this->m_fData[2] - other.m_fData[2]
		);
}

Vector3D Vector3D::operator+= (const Vector3D other) { 
	return Vector3D(
		this->m_fData[0] += other.m_fData[0],
		this->m_fData[1] += other.m_fData[1],
		this->m_fData[2] += other.m_fData[2]
	);
}
Vector3D Vector3D::operator-= (const Vector3D other) {
	return Vector3D(
		this->m_fData[0] -= other.m_fData[0],
		this->m_fData[1] -= other.m_fData[1],
		this->m_fData[2] -= other.m_fData[2]
	);
}

Vector3D Vector3D::operator+ (const float scalar){
	//Add scalar to elements
	return Vector3D(this->m_fData[0] + scalar, this->m_fData[1] + scalar, this->m_fData[2] + scalar);
}
Vector3D Vector3D::operator- (const float scalar){
	//Subtract elelements by scalar
	return Vector3D(this->m_fData[0] - scalar, this->m_fData[1] - scalar, this->m_fData[2] - scalar);
}
Vector3D Vector3D::operator* (const float scalar) {
	//Multiply elements by scalar
	return Vector3D(this->m_fData[0] * scalar, this->m_fData[1] * scalar, this->m_fData[2] * scalar);
}
Vector3D Vector3D::operator/ (const float scalar){
	//Divide elements by scalar
	if (scalar != 0) {		//Check for divde by zero
	return Vector3D(this->m_fData[0] / scalar, this->m_fData[1] / scalar, this->m_fData[2] / scalar);
	} 
	else {
		return Vector3D();	//Return empty vector
	}
}

Vector3D Vector3D::operator+= (const float scalar) {
	return Vector3D(
		this->m_fData[0] -= scalar,
		this->m_fData[1] -= scalar,
		this->m_fData[2] -= scalar
	);
}
Vector3D Vector3D::operator-= (const float scalar) {
	return Vector3D(this->m_fData[0] -= scalar, this->m_fData[1] -= scalar, this->m_fData[2] -= scalar);
}

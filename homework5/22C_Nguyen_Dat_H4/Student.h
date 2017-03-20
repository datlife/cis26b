#ifndef H4_STUDENT_H_
#define H4_STUDENT_H_
#include <string>
#include <iomanip>
class Student
{
private:
	std::string student_id_;
	std::string first_name_;
	std::string last_name_;
	double gpa_;

public:
	Student() {
		student_id_ = "-1";
		first_name_ = "N/A";
		last_name_  =  "N/A";
	}
	//Student wit only 1 ID
	Student(std::string ID){
		student_id_ = ID;
		first_name_ = "N/A";
		last_name_ = "N/A";
	}
	//Accessors
	std::string getID() const { return student_id_; }
	std::string getFirstName() const { return first_name_; }
	std::string getLastName() const { return last_name_; }
	double      getGPA()	   const { return gpa_; }
	//Mutuators
	void setID(std::string newID) { student_id_ = newID; }
	void setFirstName(std::string new_first_name) {first_name_ = new_first_name;}
	void setLastName(std::string new_last_name){last_name_ = new_last_name;}
	void setGPA(std::string newGPA) {gpa_ = stod(newGPA);}
	void showInfo();
	void showInfoIndividual();
	Student & operator = (const Student & sourceTree);
	bool operator < (const Student & sourceTree) const;
	bool operator > (const Student & sourceTree) const;
	bool operator >= (const Student & sourceTree) const;
	bool operator == (const Student & sourceTree) const;
};

#endif H4_STUDENT_H_

//Member functions definition -----------------------------------
void Student::showInfoIndividual() {
	//std::cout << student_id_ << "\t" << first_name_ << "\t" << gpa_ << std::endl;
	using namespace std;
		cout	<< std::left;
		cout	<< student_id_ <<" " 
				<< first_name_ <<" "
				<< last_name_  <<" "<<
	setprecision(2) << gpa_ << std::endl;
}
void Student::showInfo() {
	//std::cout << student_id_ << "\t" << first_name_ << "\t" << gpa_ << std::endl;
	using namespace std;
	cout<< std::left;
	cout<<setw(7) << student_id_ <<
		  setw(13) << first_name_ <<
		  setw(20) << last_name_ <<
		  fixed<< setprecision(2)  <<
		  gpa_ << std::endl;
}
Student& Student::operator= (const Student & sourceTree){
	if (this != &sourceTree){
		student_id_ = sourceTree.getID();
		first_name_ = sourceTree.getFirstName();
		last_name_ = sourceTree.getLastName();
		gpa_ = sourceTree.getGPA();
	}
	return *this;
}
bool Student::operator < (const Student & sourceTree) const{
	return   this->getID() < sourceTree.getID();
}
bool Student::operator > (const Student & sourceTree) const{
	return student_id_ > sourceTree.getID();
}
bool Student::operator >= (const Student & sourceTree) const{
	return student_id_ >= sourceTree.getID();
}

bool Student::operator == (const Student & sourceTree) const{
	return student_id_ == sourceTree.getID();
}
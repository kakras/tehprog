#include <iostream>
#include <string>
using namespace std;
struct Employee {
	string name;
	int age;
	double salary;
	Employee* next;
};
struct functions {
	Employee* list;
	void AddBeg(Employee* &fEmp, string name, int age, double salary) {
		Employee* employee = new Employee;
		employee->name = name;
		employee->age = age;
		employee->salary = salary;
		employee->next = fEmp;
		fEmp = employee;
	}
	void end(Employee* &fEmp, string name, int age, double salary) {
		Employee* employee = new Employee;
		employee->name = name;
		employee->age = age;
		employee->salary = salary;
		employee->next = fEmp;
		if (fEmp == nullptr) {
			employee->next = nullptr;
			fEmp = employee;
		}
		else {
			Employee* tmp = fEmp;
			while (tmp->next != nullptr)
				tmp = tmp->next;
			employee->next = nullptr;
			tmp->next = employee;
		}
	}
	void after(Employee* fEmp, string pered, string name, int age, double salary) {
		if (fEmp == nullptr) {
			return;
		}
		Employee* tmp = fEmp;
		while (tmp->next != nullptr and tmp->name != pered)
			tmp = tmp->next;
		if (tmp->next == nullptr and tmp->name != pered) {
			return;
		}
		Employee* employee = new Employee;
		employee->name = name;
		employee->age = age;
		employee->salary = salary;
		employee->next = fEmp->next;
		fEmp->next = employee;
	}
	void before(Employee* fEmp, string posle, string name, int age, double salary) {
		if (fEmp == nullptr) {;
			return;
		}
		if (fEmp->name == posle) {
			AddBeg(fEmp, name, age, salary);
			return;
		}
		Employee* prev = fEmp, * tmp = fEmp->next;
		while (tmp->next != nullptr and tmp->name != posle) {
			tmp = tmp->next;
			prev = prev->next;
		}
		if (tmp->next == nullptr and tmp->name != posle) {
			return;
		}
		Employee* employee = new Employee;
		employee->name = name;
		employee->age = age;
		employee->salary = salary;
		employee->next = tmp;
		prev->next = employee;
	}
	void del(Employee* &fEmp, string now) {
		if (fEmp == nullptr) {
			return;
		}
		Employee* tmp = fEmp;
		if (fEmp->name == now) {
			fEmp = fEmp->next;
			delete tmp;
			return;
		}
		if (fEmp->next == nullptr) {
			return;
		}
		Employee* prev = fEmp;
		tmp = fEmp->next;
		while (tmp->next != nullptr and tmp->name != now) {
			tmp = tmp->next;
			prev = prev->next;

		}
		if (tmp->next == nullptr and tmp->name != now) {
			return;
		}
		if (tmp->name == now) {
			prev->next = tmp->next;
			delete tmp;
			return;
		}
	}
	void print(Employee* fEmp) {
		if (fEmp == nullptr) {
			return;
		}
		Employee* tmp = fEmp;
		while (tmp != nullptr) {
			cout << "Name: " << tmp->name << " Age: " << tmp->age << " Salary: " << tmp->salary << endl;
			tmp = tmp->next;
		}
		cout << endl;
	}

};
int main() {
	Employee* employee = new Employee{ "Kate", 23, 5792.33 };
	functions func;
	func.list = employee;
	func.AddBeg(func.list, "Bob", 44, 8825.2);
	func.end(func.list, "Drake", 21, 8719.1);
	func.after(func.list, "Bob", "Liza", 32, 9423.11);
	func.before(func.list, "Drake",  "Robby", 51, 4236.11);
	func.print(func.list);
	func.del(func.list, "Drake");
	func.print(func.list);
	delete employee;
	return 0;
}
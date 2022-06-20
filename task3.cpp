#include "task3.hpp"
#include <numeric>

void task3()
{
    task2::FullName fn;
    fn.name("Ivan");
    fn.fam("Ivanov");
    fn.otch("Ivanovich");

    task2::Student s;
    *s.mutable_name() = fn;
    s.add_grad(2);
    s.add_grad(3);
    s.add_grad(4);
    s.add_grad(5);
    s.add_grad(4);
    s.add_grad(3);
    s.add_grad(2);
    s.add_grad(3);
    s.avg_score(std::accumulate(s.grades().begin(), s.grades().end(), 0) / s.grades().size());

    SG::StudentsGroup sg;
    sg.add_student(s);
    sg.Save();

    SG::StudentsGroup new_sg;
    new_sg.Open();
    std:: cout << new_sg.GetAllInfo(fn) << std::endl;
}


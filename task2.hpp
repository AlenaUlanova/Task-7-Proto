#include <iostream>
#include <numeric>
#include <fstream>
#include "src-gen/task2.pb.h"

void task2()
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

    task2::StudentsGroup sg;
    *sg.add_students() = s;

    std::ofstream out("student.bin", std::ios_base::binary);
    sg.SerializeToOstream(&out);
    out.close();

    task2::StudentsGroup new_sg;
    std::ifstream in("student.bin", std::ios_base::binary);
    if (new_sg.ParseFromIstream(&in))
    {
        std::cout << new_sg.students(0).name().fam() << std::endl;
        std::cout << new_sg.students(0).avg_score() << std::endl;
    }
    else
    {
        std::cout << "Error!" << std::endl;
    }
    in.close();
}

#include <iostream>
#include <vector>
#include <fstream>
#include "src-gen/task2.pb.h"

namespace SG
{
    class IRepository {
        virtual void Open() = 0; // бинарная десериализация в файл 
        virtual void Save() = 0; // бинарная сериализация в файл
    };
    class IMethods {
        virtual double GetAverageScore(const FullName& name) = 0;
        virtual string GetAllInfo(const FullName& name) = 0;
        virtual string GetAllInfo() = 0;
    };

    class StudentsGroup: public IRepository, public IMethods
    {
    private:
        std::vector<task2::Student> m_students;
    public:
        void add_student(const task2::Student &s)
        {
            m_students.push_back(s);
        }

        double GetAverageScore(const task2::FullName &name)
        {
            auto it = std::find_if(m_students.begin(), m_students.end(), [&](const task2::Student &s)
            {
                return tie(s.name().name(), s.name().fam(), s.name().otch()) ==
                tie(name.name(), name.fam(), name.otch());
            });

            if (it == m_students.end())
            {
                return 0.0;
            }

            return it->avg_score();
        }

        std::string GetAllInfo(const task2::FullName &name)
        {
            auto it = std::find_if(m_students.begin(), m_students.end(), [&](const task2::Student &s)
            {
                return tie(s.name().name(), s.name().fam(), s.name().otch()) ==
                tie(name.name(), name.fam(), name.otch());
            });

            if (it == m_students.end())
            {
                return {};
            }

            std::string temp = "Имя: " + it->name().name() + ' ' + it->name().fam() + ' ' + it->name().otch() + '\n';
            temp += "Оценки: ";
            for (int i = 0; i < it->grades().size(); ++i)
            {
                temp += std::to_string(it->grades(i)) + "; ";
            }
            temp += '\n';
            temp += "Средний балл: " + std::to_string(it->avg_score()) + "\n\n";

            return temp;
        }

        std::string GetAllInfo()
        {
            std::string temp;

            std::for_each(m_students.begin(), m_students.end(), [&](const task2::Student &s)
            {
                temp += GetAllInfo(s.name());
            });

            return temp;
        }

        void Save()
        {
            std::ofstream out("data.bin", std::ios_base::binary);
            auto size = m_students.size();
            out.write(reinterpret_cast<char*>(&size), sizeof(size));
            std::for_each(m_students.begin(), m_students.end(), [&](const task2::Student &s)
            {
                s.SerializeToOstream(&out);
            });
            out.close();
        }

        void Open()
        {
            std::ifstream in("data.bin", std::ios_base::binary);
            size_t size = 0;
            in.read(reinterpret_cast<char*>(&size), sizeof(size));
            while (size--)
            {
                task2::Student s;
                s.ParseFromIstream(&in);
                m_students.push_back(std::move(s));
            }
            in.close();
        }

        virtual ~StudentsGroup() {};
    };
}

void task3();

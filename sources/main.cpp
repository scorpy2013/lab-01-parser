int main() {
    //...
    std::ifstream file{jsonPath};
    if (!file) {
        throw std::runtime_error{"unable to open json: " + jsonPath};
    }

    json data;
    file >> data;

    std::vector<Student> students;
    for (auto const& student : data.at("items")) {
        students.push_back(Student{student});
    }
    //...
}

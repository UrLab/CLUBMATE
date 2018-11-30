#include "smart_matrix_class.cpp"

void test_rollingmatrix(void){
    std::cout << "Start" << std::endl;
    RollingMatrix rm = RollingMatrix(5, 10);
    rm.print();
    uint32_t column[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    for (int i = 0; i < 5; i++) {
        rm.push_right(column);
        rm.print();
    }

    uint32_t column2[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    for (int i = 0; i < 5; i++) {
        rm.push_left(column2);
        rm.print();
    }

    uint32_t row[5] = {3, 3, 3, 3, 3};
    for (int i = 0; i < 10; i++) {
        rm.push_top(row);
        rm.print();
    }

    uint32_t row2[5] = {4, 4, 4, 4, 4};
    for (int i = 0; i < 10; i++) {
        rm.push_bottom(row2);
        rm.print();
    }
    std::cout << "End" << std::endl;
}

void test_cmmatrix() {
    std::cout << "Start" << std::endl;
    coord crate_order[4] = {
        {0, 0}, {1, 0},
        {1, 1}, {0, 1},
    };
    CMMatrix cm = CMMatrix(8, 10, crate_order);
    cm.print();
    cm.render();
    cm.aprint();

    uint32_t column[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    for (int i = 0; i < 8; i++) {
        cm.push_right(column);
        cm.print();
        cm.render();
        cm.aprint();
    }

    uint32_t column2[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    for (int i = 0; i < 8; i++) {
        cm.push_left(column2);
        cm.print();
        cm.render();
        cm.aprint();
    }

    uint32_t row[8] = {3, 3, 3, 3, 3, 3, 3, 3};
    for (int i = 0; i < 10; i++) {
        cm.push_top(row);
        cm.print();
        cm.render();
        cm.aprint();
    }

    uint32_t row2[8] = {4, 4, 4, 4, 4, 4, 4, 4};
    for (int i = 0; i < 10; i++) {
        cm.push_bottom(row2);
        cm.print();
        cm.render();
        cm.aprint();
    }
    std::cout << "End" << std::endl;
}

void test_cmmatrix2() {
    std::cout << "Start" << std::endl;
    coord crate_order[2] = {
        {0, 0}, {1, 0},
    };
    CMMatrix cm = CMMatrix(8, 5, crate_order);
    cm.print();
    cm.render();
    cm.aprint();

    uint32_t column[5] = {1, 1, 1, 1, 1};
    for (int i = 0; i < 8; i++) {
        cm.push_right(column);
        cm.print();
        cm.render();
        cm.aprint();
    }

    uint32_t column2[5] = {2, 2, 2, 2, 2};
    for (int i = 0; i < 8; i++) {
        cm.push_right(column2);
        cm.print();
        cm.render();
        cm.aprint();
    }

    std::cout << "End" << std::endl;
}

void test_cmmatrix3() {
    std::cout << "Start" << std::endl;
    coord crate_order[1] = {
        {0, 0},
    };
    CMMatrix cm = CMMatrix(4, 5, crate_order);
    cm.print();
    cm.render();
    cm.aprint();

    uint32_t column[5] = {1, 1, 1, 1, 1};
    for (int i = 0; i < 4; i++) {
        cm.push_right(column);
        cm.print();
        cm.render();
        cm.aprint();
    }

    uint32_t column2[5] = {2, 2, 2, 2, 2};
    for (int i = 0; i < 4; i++) {
        cm.push_left(column2);
        cm.print();
        cm.render();
        cm.aprint();
    }

    uint32_t row[4] = {3, 3, 3, 3};
    for (int i = 0; i < 5; i++) {
        cm.push_top(row);
        cm.print();
        cm.render();
        cm.aprint();
    }

    uint32_t row2[4] = {4, 4, 4, 4};
    for (int i = 0; i < 5; i++) {
        cm.push_bottom(row2);
        cm.print();
        cm.render();
        cm.aprint();
    }

    std::cout << "End" << std::endl;
}

int main(void) {
    // test_rollingmatrix();
    test_cmmatrix2();
}

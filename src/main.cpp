#include <GEDAD.hpp>
#include <array>
#include <chrono>
#include <iostream>

using namespace std;

int main() {
    size_t                   buffer_size = 36;
    ad::GEDAD<int, float, 3> gedad(buffer_size);

    gedad.printBuffer();
    cout << endl;

    array<int, 3> data = {1, 2, 3};
    for (size_t i = 0; i < buffer_size; ++i) {
        gedad.pushToBuffer(data);
    }

    gedad.printBuffer();
    cout << endl;

    array<ad::AlphaBeta<float>, 3> alpha_beta;
    fill(alpha_beta.begin(), alpha_beta.end(), ad::AlphaBeta<float>(1.0f, 0.01f));

    gedad.calEuclideanDistThresh(0, 18, 18, 18, 4, 6, 1, 10, alpha_beta);
    cout << endl;

    size_t times = 3;
    for (size_t i = 0; i < times; ++i) {
        gedad.pushToBuffer(data);
        auto start        = chrono::high_resolution_clock::now();
        auto anomaly_type = gedad.isLastViewAnomaly(0.05f);
        auto end          = chrono::high_resolution_clock::now();
        switch (anomaly_type) {
        case ad::AnomalyType::Anomaly:
            cout << "anomaly detected at index " << i << endl;
            break;
        case ad::AnomalyType::Normal:
            cout << "normal at index " << i << endl;
            break;
        case ad::AnomalyType::Unknown:
            cout << "unknown at index " << i << endl;
            break;
        }
        cout << "time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "us" << endl;
        cout << endl;
    }

    return 0;
}

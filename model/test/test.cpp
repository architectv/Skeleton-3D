#include "../model.h"
using std::cout;

void run_test() {
    Model *x = new Model;

    int err = 0;
    // TESTING ADDING AND HAVING

    Point p1(0, 0, 0, 0);
    x->AddPoint(&p1);
    if (x->GetPoints().size() != 1) {
        err++;
    }
    if (!x->IsPointInModel(&p1)) {
        err++;
    }

    Point p2(2.3, 45.32, -34, 1);
    x->AddPoint(&p2);
    if (x->GetPoints().size() != 2) {
        err++;
    }
    if (!x->IsPointInModel(&p2)) {
        err++;
    }

    Point p3(0, 0, 0, 0);
    x->AddPoint(&p3);
    if (x->GetPoints().size() != 2) {
        err++;
    }
    if (!x->IsPointInModel(&p3)) {
        err++;
    }

    Edge e1(&p1, &p2);
    x->AddEdge(&e1);
    if (x->GetEdges().size() != 1) {
        err++;
    }
    if (!x->IsEdgeInModel(&e1)) {
        err++;
    }

    Edge e1fake(&p2, &p1);
    x->AddEdge(&e1fake);
    if (x->GetEdges().size() != 1) {
        err++;
    }
    if (!x->IsEdgeInModel(&e1fake)) {
        err++;
    }

    Point p4(2, 2, 3, 4);
    Point p5(3, 4, 5, 6);
    Edge e2(&p4, &p5);

    Point p6(4, 65, 43, 4);
    Point p7(2, 7, 4, 3);
    Edge e3(&p6, &p7);

    vector<Edge *> edgestest;
    edgestest.push_back(&e1);
    edgestest.push_back(&e2);
    edgestest.push_back(&e3);

    Surface surface1(edgestest);

    x->AddSurface(&surface1);
    if (x->GetSurfaces().size() != 1) {
        err++;
    }
    if (!x->IsSurfaceInModel(&surface1)) {
        err++;
    }

    // DELETING

    x->DeletePoint(&p1);
    if (x->IsPointInModel(&p1)) {
        err++;
    }
    
    x->DeleteEdge(&e1);
    if (x->IsEdgeInModel(&e1)) {
        err++;
    }

    x->DeleteSurface(&surface1);
    if (x->IsSurfaceInModel(&surface1)) {
        err++;
    }

    if (err) {
        cout << "\n\tERROR\n\n";
    } else {
        cout << "\n\tOK\n\n";
    }

    delete x;

}

int main() {
    run_test();
}
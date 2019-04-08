#include "../model.h"
using std::cout;

void run_test() {
    Model *x = new Model;

    int err = 0;
    // TESTING ADDING AND HAVING

    Point p1(0, 0, 0);
    x->AddPoint(p1);
    if (x->GetPoints().size() != 1) {
        err++;
    }

    if (!x->IsPointInModel(p1)) {
        err++;
    }

    Point p2(2.3, 45.32, -34);
    x->AddPoint(p2);
    if (x->GetPoints().size() != 2) {
        err++;
    }
    if (!x->IsPointInModel(p2)) {
        err++;
    }

    Point p3(0, 0, 0);
    x->AddPoint(p3);
    if (x->GetPoints().size() != 2) {
        err++;
    }
    if (!x->IsPointInModel(p3)) {
        err++;
    }

    Edge e1(0, 1);
    x->AddEdge(e1);

    if (x->GetEdges().size() != 1) {
        err++;
    }

    if (!x->IsEdgeInModel(e1)) {
        err++;
    }

    Edge e1fake(1, 0);
    x->AddEdge(e1fake);
    if (x->GetEdges().size() != 1) {
        err++;
    }
    if (!x->IsEdgeInModel(e1fake)) {
        err++;
    }


    Point p4(2, 2, 3);
    Point p5(3, 4, 5);
    x->AddPoint(p4);
    x->AddPoint(p5);
    Edge e2(2, 3);
    x->AddEdge(e2);
    if (!x->IsEdgeInModel(e2)) {
        err++;
    }

    Point p6(4, 65, 43);
    Point p7(2, 7, 4);
    x->AddPoint(p6);
    x->AddPoint(p7);
    Edge e3(4, 5);
    x->AddEdge(e3);
    if (!x->IsEdgeInModel(e3)) {
        err++;
    }

    vector<int> edgestest;
    edgestest.push_back(0);
    edgestest.push_back(1);
    edgestest.push_back(2);

    Surface surface1(edgestest);

    x->AddSurface(surface1);
    if (x->GetSurfaces().size() != 1) {
        err++;
    }
    if (!x->IsSurfaceInModel(surface1)) {
        err++;
    }

    // DELETING


    x->DeleteSurface(surface1);
    if (x->GetSurfaces().size() != 0) {
        err++;
    }
    x->AddSurface(surface1);

    x->DeleteEdge(e1);
    if (x->IsEdgeInModel(e1)) {
        err++;
    }
    if (x->GetSurfaces().size() != 0) {
        err++;
    }
    x->AddEdge(e1);
    x->AddSurface(surface1);
    
    delete x;
    x = new Model;
    Point po0(0, 0, 0);
    x->AddPoint(po0);
    Point po1(1, 1, 1);
    x->AddPoint(po1);
    Point po2(2, 3, 4);
    x->AddPoint(po2);
    Point po3(3, 4, 6);
    x->AddPoint(po3);
    Point po4(4, 5, 9);
    x->AddPoint(po4);
    Point po5(5, 2, 9);
    x->AddPoint(po5);

    Edge ed0(0, 1);
    Edge ed1(2, 3);
    Edge ed2(4, 5);
    x->AddEdge(ed0);
    x->AddEdge(ed1);
    x->AddEdge(ed2);

    vector<int> edgeses;
    edgeses.push_back(0);
    edgeses.push_back(1);
    edgeses.push_back(2);
    Surface sur0(edgeses);
    x->AddSurface(sur0);
    //x->PrintData();
    
    size_t checjPointSize = x->GetPoints().size();
    size_t checkEdgeSize = x->GetEdges().size();
    size_t checkSurfaceSize = x->GetSurfaces().size();

    x->DeleteSurface(sur0);
    if (x->IsSurfaceInModel(sur0) || x->GetSurfaces().size() != checkSurfaceSize - 1) {
        err++;
    }
    x->AddSurface(sur0);

    x->DeleteEdge(ed0);
    if (x->IsEdgeInModel(ed0) || x->GetEdges().size() != checkEdgeSize - 1) {
        err++;
    }
    if (x->IsSurfaceInModel(sur0) || x->GetSurfaces().size() != checkSurfaceSize - 1) {
        err++;
    }
    x->AddEdge(ed0);
    x->AddSurface(sur0);
    //x->PrintData();

    x->DeletePoint(po0);
    //x->PrintData();
    if (x->IsPointInModel(po0) || x->GetPoints().size() != checjPointSize - 1) {
        err++;
    }
    if (x->GetEdges().size() != checkEdgeSize - 1) {
        err++;
    }
    if (x->GetSurfaces().size() != checkSurfaceSize - 1) {
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
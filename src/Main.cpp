#include <ColaModel.hpp>

int main(int argc, char ** argv) {
  clock_t overall_start_time = clock();
  ColaModel * model;
  model = new ColaModel();
  clock_t read_start_time = clock();
  model->read(argv[1]);
  clock_t read_duration = clock() - read_start_time;
  model->options()->set_int_option(LOG_LEVEL, 1);
  clock_t solution_start_time = clock();
  ProblemStatus s = model->solve();
  clock_t solution_duration = clock() - solution_start_time;
  clock_t overall_duration = clock() - overall_start_time;
  if (s==OPTIMAL) {
    model->get_conic_constraints()->dump_cones_brief();
    //model->get_conic_constraints()->dump_cones();
    //model->print_solution();
    model->report_feasibility();
    model->print_stats();
    std::cout << "Obj value is " << model->getObjValue() << std::endl;
    // report time
    std::cout << "Time spent on reading model (in secs) " <<
      double(read_duration) / double(CLOCKS_PER_SEC) << std::endl;
    std::cout << "Time spent on solve function call (in secs) " <<
      double(solution_duration) / double(CLOCKS_PER_SEC) << std::endl;
    std::cout << "Total time spent (in secs) " <<
      double(overall_duration) / double(CLOCKS_PER_SEC) << std::endl;
    // const double * sol = model->getColSolution();
    // for (int i=0; i<model->getNumCols(); ++i) {
    //   std::cout << sol[i] << std::endl;
    // }
  }
  else {
    switch(s) {
    case ABANDONED:
      std::cerr << "Cola: Problem is abandoned." << std::endl;
      break;
    case PRIMAL_INFEASIBLE:
      std::cout << "Cola: Primal infeasible." << std::endl;
      break;
    case DUAL_INFEASIBLE:
      std::cout << "Cola: Dual infeasible." << std::endl;
      break;
    case PRIMAL_OBJECTIVE_LIMIT_REACHED:
      std::cerr << "Cola: Primal objective limit reached." << std::endl;
      break;
    case DUAL_OBJECTIVE_LIMIT_REACHED:
      std::cerr << "Cola: Dual objective limit reached." << std::endl;
      break;
    case ITERATION_LIMIT_REACHED:
      std::cerr << "Cola: Iteration limit reached." << std::endl;
      break;
    default:
      std::cerr << "Cola: Unknown problem status." << std::endl;
      break;
    }
  }
  delete model;
  return 0;
}

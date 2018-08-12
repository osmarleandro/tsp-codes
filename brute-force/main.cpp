#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::getline;
using std::stoi;
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <algorithm>
using std::copy;
using std::next_permutation;
using std::sort;

int **reading();
void see(int **matrix, int n);
void see(int *vector, int n);

int *brute_force(int **adj, int n);
int *generateSolution(int n);
int cost(int **adj, int *sol, int n);
int *swap(int *sol, int n, int i, int j);
int *unshift(int *sol, int n);

int main()
{
  reading();
  return 0;
}

int **reading()
{
  string::size_type sz;
  ifstream instance;
  string line;
  int **adj, n;

  instance.open("instance.tsp");
  if (instance.is_open())
  {
    getline(instance, line);
    n = stoi(line, &sz);
    adj = new int *[n];

    for (int i = 0; i < n; i++)
    {
      adj[i] = new int[n];
      for (int j = 0; j < n; j++)
      {
        getline(instance, line);
        adj[i][j] = stoi(line, &sz);
      }
    }
    instance.close();
  }

  else
    cout << "Unable to open file";

  see(adj, n);
  brute_force(adj, n);

  return adj;
}

void see(int **matrix, int n)
{
  cout << "The Matrix" << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      cout << matrix[i][j] << "\t";
    cout << endl;
  }
}

void see(int *vector, int n)
{
  for (int i = 0; i < n; i++)
    cout << vector[i] << "\t";
  cout << endl;
}

int *brute_force(int **adj, int n)
{
  int iter = 1;
  // initial solution and cost [ 0, 1, 2, 3, 4]
  int *bestSol = generateSolution(n);

  // calculing cycle cost
  int bestCost = cost(adj, bestSol, n);

  cout << "\nInitial solution cost: " << bestCost << endl;
  cout << "Initial solution: ";
  see(bestSol, n);
  cout << endl;

  int *current = new int[n];
  copy(bestSol, bestSol + n, current);
  sort(current, current + n);

  while (next_permutation(current, current + n))
  {
    // calculing cost of current solution for next permutation
    int currentCost = cost(adj, current, n);
    if (currentCost < bestCost)
    {
      copy(current, current + n, bestSol);
      bestCost = currentCost;
    }
    iter++;
  };

  // show the final result
  cout << "Iterations: " << iter << endl;
  cout << "\nBest solution cost: " << bestCost << endl;
  cout << "Best solution: ";
  see(bestSol, n);

  return bestSol;
}

int *generateSolution(int n)
{
  int *solution = new int[n];
  for (int i = 0; i < n; i++)
    solution[i] = i;
  return solution;
}

int cost(int **adj, int *sol, int n)
{
  int total_cost = 0;
  for (int i = 0; i <= n - 1; i++)
  {
    // if [i] is the last index, [j] equals to first: cost of first city return
    int j = (i == n - 1) ? 0 : (i + 1);
    total_cost = total_cost + adj[sol[i]][sol[j]];
  }
  return total_cost;
}

int *swap(int *sol, int n, int i, int j)
{
  int *vector = new int[n];
  copy(sol, sol + n, vector);

  int tmp = vector[i];
  vector[i] = vector[j];
  vector[j] = tmp;
  return vector;
}

int *unshift(int *sol, int n)
{
  const int LIMIT = n - 1;
  int *vector = new int[n];
  vector[0] = sol[LIMIT];

  for (int i = 1; i <= LIMIT; i++)
    vector[i] = sol[i - 1];

  see(vector, n);
  return vector;
}
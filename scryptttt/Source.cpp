#include <iostream>
#include <vector>
#include <Windows.h>
#include "globalStructures.h"
#include"Map.h"

class Game {
private:
  Map map;
public:
  Game() {
    map.create({ 20, 20 });
  }
};

class Neuron {
private:
  float input;
  float output;

public:

};

class Synapse {
private:
  float weight;
  int input_neuron;
  int output_neuron;

public:
  Synapse(int input_neuron, int output_neuron) {
    this->input_neuron = input_neuron;
    this->output_neuron = output_neuron;
  }
};

class Network {
private:
  std::vector<Synapse> synapse;
  std::vector<Neuron> layer_input;
  std::vector<Neuron> layer_output;

public:
  Network(int input, int output) {
    for (int i = 0; i < input * output; i++) {
      weight.push_back((float)(rand() % 11) / 10);
      std::cout << weight[i] << '\n';
    }
  }

  Network() {

  }
};

int main() {
  
  Network neuro_network(2, 1);

  return 0;
}
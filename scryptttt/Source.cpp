#include <iostream>
#include <vector>
#include <Windows.h>
#include "Neuron.h"
#include "Synapse.h"

const int INPUT_NEURONS = 2;
const int HIDDEN_NEURONS = 6;
const int OUTPUT_NEURONS = 2;

class Network {
private:
  Neuron inputLayer[INPUT_NEURONS];
  Neuron hiddenLayer[HIDDEN_NEURONS];
  Neuron outputLayer[OUTPUT_NEURONS];
  Synapse weight[INPUT_NEURONS * HIDDEN_NEURONS * OUTPUT_NEURONS];

public:
  Network(float input[INPUT_NEURONS]) {
    for (int i = 0; i < INPUT_NEURONS; i++) {
      inputLayer[i].addInput(input[i]);
    }

    int w = 0;
    for (int input_neuron = 0; input_neuron < INPUT_NEURONS; input_neuron++) {
      for (int hidden_neuron = 0; hidden_neuron < HIDDEN_NEURONS; hidden_neuron++) {
        weight[w].inputNeuron = input_neuron;
        weight[w].outputNeuron = hidden_neuron;
        weight[w].setInput(inputLayer[input_neuron].getOutput());
        hiddenLayer[hidden_neuron].addInput(weight[w].getOutput());
        w++;
      }
    }
    for (int hidden_neuron = 0; hidden_neuron < HIDDEN_NEURONS; hidden_neuron++) {
      for (int output_neuron = 0; output_neuron < OUTPUT_NEURONS; output_neuron++) {
        weight[w].inputNeuron = hidden_neuron;
        weight[w].outputNeuron = output_neuron;
        weight[w].setInput(hiddenLayer[hidden_neuron].getOutput());
        outputLayer[output_neuron].addInput(weight[w].getOutput());
        w++;
      }
    }

    std::cout << outputLayer[0].getOutput() << '\t' << outputLayer[1].getOutput() << '\n';
  }
};

int main() {
  srand(1);
  float input[INPUT_NEURONS] = { 0.0, 1.0 };
  Network neuro_network(input);

  return 0;
}
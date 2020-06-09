#include "Neuron.h"

void Neuron::execute() {
  out = 0;
  for (int i = 0; i < in.size(); i++) {
    out += in[i];
  }
}

Neuron::Neuron() {
  out = 0;
}

void Neuron::addInput(float inputSynapse) {
  in.push_back(inputSynapse);
}

float Neuron::getOutput() {
  execute();
  return out;
}
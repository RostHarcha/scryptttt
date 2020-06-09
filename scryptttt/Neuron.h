#pragma once
#include <vector>
class Neuron {
private:
  std::vector<float> in;
  float out;
  void execute();

public:
  Neuron();
  void addInput(float inputSynapse);
  float getOutput();
};
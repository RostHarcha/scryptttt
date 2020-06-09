#pragma once
class Synapse {
private:
  float in;
  float weight;
  float out;
  float calculate();

public:
  int inputNeuron;
  int outputNeuron;
  Synapse();
  void setInput(float input);
  float getOutput();
};


#include "Synapse.h"
#include <iostream>

#define randWeight ((float)(rand() % 11) / 1)

float Synapse::calculate() {
  return in * weight;
}

Synapse::Synapse() {
  weight = (float)(rand() % 11) / 10;
  setInput(0);
}

void Synapse::setInput(float input) {
  in = input;
  out = calculate();
}

float Synapse::getOutput() {
  return out;
}
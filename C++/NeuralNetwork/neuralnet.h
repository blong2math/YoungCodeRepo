#ifndef NEURALNET
#define NEURALNET

/* 
 * Auth: Young 
 * Date: 2014/7/16
 * Lang: C++ 11
 */

#include <stdlib.h>
#include <math.h>
#include <time.h>

/* This is a class to store and fetch the weights of neural net */
template <typename E> // E = float or double based on the accuracy you need
class Weights{ 
private:
	int num_input; // The number of last layer units(input)
	int num_output; // The number of this layer units(output)
	E** weights; // The connection intensity of units to units

public:
	Weights(){
		
	}

	Weights(int in, int out){
		num_input = in;
		num_output = out;
		weights = new E*[num_input];
		for (int f_unit = 0; f_unit < num_input; f_unit++){
			weights[f_unit] = new E[num_output];
		}

		srand((unsigned)time(NULL));
		for (int f_layer = 0; f_layer < num_input; f_layer++){
			for (int l_layer = 0; l_layer < num_output; l_layer++){
				weights[f_layer][l_layer] = ((float)(rand() % 200)) * 0.01 - 1;
			}
		}
	}

	void setWeight(int i, int o, E w){
		weights[i][o] = w;
	}

	E getWeight(int i, int o){
		return weights[i][o];
	}
};


/*     This class is a neural net training with back-propagation algorithm. */
/* The function of each unit is a sigmoid function.                         */
/*     Constructing with the number of layers and the numbers of units in   */
/* each layers.                                                             */
template <typename P> // P is the precision(float or double)
class BPNeuralNet{  // Back propagation neural net
private:
	int num_layers; // The number of layers
	int* num_units; //  The number of units in each layers(input --> output)
	Weights<P>* weights; // The connection intensity of two units

	double learning_rate = 10; // The rate to adjust weights
	
	P sigmoid(P x){
		return 1 / (1 + exp(-((double)x)));
	}

	void forwardPropagation(P* input){
		for (int unit = 0; unit < num_units[0]; unit++){
			activations[0][unit] = input[unit];
		}

		for (int layer = 1; layer < num_layers; layer++){ // Each layer
			for (int unit = 0; unit < num_units[layer]; unit++){ // Each later unit
				P input = 1.0; // Bias Term;
				for (int f_unit = 0; f_unit < num_units[layer - 1]; f_unit++){ // Each former unit
					input += (weights[layer - 1]).getWeight(f_unit, unit) * activations[layer - 1][f_unit];
				}
				activations[layer][unit] = sigmoid(input);
			}
		}
	}

	void backPropagation(P* out){
		for (int unit = 0; unit < num_units[num_layers - 1]; unit++){
			errors[num_layers - 1][unit] = out[unit] - activations[num_layers - 1][unit];
		}
		 
		for (int layer = num_layers - 1; layer > 1; layer--){ // Each layer
			for (int unit = 0; unit < num_units[layer - 1]; unit++){ // Each former unit
				P backerror = 0;
				for (int l_unit = 0; l_unit < num_units[layer]; l_unit++){ // Each later unit
					backerror += (weights[layer - 1]).getWeight(unit, l_unit) * errors[layer][l_unit];
				}
				backerror *= activations[layer - 1][unit] * (1 - activations[layer - 1][unit]);
				errors[layer - 1][unit] = backerror;
			}
		}
	}

	void adjustWeights(){
		for (int layer = 0; layer < num_layers - 1; layer++){ // Each layer
			for (int unit = 0; unit < num_units[layer]; unit++){ // Each former unit
				for (int l_unit = 0; l_unit < num_units[layer + 1]; l_unit++){ // Each later unit
					P deltaw = learning_rate * errors[layer + 1][l_unit] * activations[layer][unit];
					weights[layer].setWeight(unit, l_unit, weights[layer].getWeight(unit, l_unit) + deltaw);
				}
			}
		}
	}

public:
	P** activations; // The activation value of each unit immediately
	P** errors; // The error value of each unit immediately (Input layer is always 0);

	BPNeuralNet(){

	}

	BPNeuralNet(int layers, int* units){
		num_layers = layers;
		num_units = new int[layers];
		activations = new double*[num_layers];
		errors = new double*[num_layers];
		for (int i = 0; i < layers; i++){
			num_units[i] = units[i];
			activations[i] = new double[num_units[i]];
			if (i != 0){
				errors[i] = new double[num_units[i]]; // Because there is no input layer error
			}
		}
		weights = new Weights<P>[layers - 1];
		for (int i = 0; i < layers - 1; i++){
			weights[i] = Weights<P>(num_units[i], num_units[i + 1]);
		}
	}

	/* The function to give a training case to adjust weights */
	void train(P* in, P* out){
		forwardPropagation(in);
		backPropagation(out);
		adjustWeights();
	}

	/* The function to predict with a row of inputs */
	P* predict(P* in){
		forwardPropagation(in);
		return activations[num_layers - 1];
	}

	void setLearningRate(double lr){
		learning_rate = lr;
	}
};

#endif
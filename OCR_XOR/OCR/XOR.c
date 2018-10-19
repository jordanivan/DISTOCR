#include "XOR.h"
#include <math.h>

static double Random()
{
	// return a random number between 0 and 1
	return (double)rand()/(double)RAND_MAX;
}

static double sigmoid(double x)
{
	// sigmoid function
	return (1.0 / (1.0 + exp(-x)));
}

/*
static d_sigmoid(double x)
{ 
	// derivate of sigmoid function
	// with x which is the value of sigmoid(x)
	return x * (1.0 - x);
}*/


struct Network
{
    int nbInput; // number of inputs
    int nbLayer; // number of layers

    double *InputValue; // array of input values
    double *OutputValue; // array of output values

    //array of weight and delta weight
    double *WeightIH; // between input and hidden layer
    double *deltaWeightIH;
    double *WeightHO; // between hidden and output layer
    double *deltaWeightHO;

    //array of bias and delta bias
    double *BiasH;
    double *deltaBiasH;

    //bias of output
    double BiasO;
    double deltaBiasO;

    //output of hidden layer
    double *OutputH;
    double *deltaHidden;

    //output and delta output
    double OutputO;
    double deltaOutputO;
    
    double Error; // error rate
    double eta; // learning rate
    double alpha;

    double Output_p; // the output of the 

};

struct Network Initialize_Net()
{
  struct Network nn;
  nn.nbInput = 2;
  nn.nbLayer = 3; // input, hidden, output

  nn.InputValue = malloc(sizeof(double)*4 * 2); // 4 patterns * 2 inputs
  nn.OutputValue = malloc(sizeof(double)*4); // result of 00 01 10 11

  nn.WeightIH = malloc(sizeof(double)*2 * 3); //nbInput * nbLayer
  nn.deltaWeightIH = malloc(sizeof(double)*2 * 3);

  nn.WeightHO = malloc(sizeof(double)*3); //nbLayer
  nn.deltaWeightHO = malloc(sizeof(double)*3);

  nn.BiasH = malloc(sizeof(double)*3); //nbLayer
  nn.deltaBiasH = malloc(sizeof(double)*3);

  nn.BiasO = Random();
  nn.deltaBiasO = 0.0;

  nn.OutputH = malloc(sizeof(double)*3); //nbLayer
  nn.deltaHidden = malloc(sizeof(double)*3);

  nn.OutputO = 0;
  nn.deltaOutputO = 0.0;

  nn.Error = 0.0;
  nn.eta = 0.5;
  nn.alpha = 0.95; 

  nn.Output_p = 0.0;

  return nn;
}
void Initialize_Val(struct Network *nn)
{
//Initialize input and output values
  
  // 0 0 -> 0
  *((*nn).InputValue) = 0;
  *((*nn).InputValue +1) = 0;
  *((*nn).OutputValue) = 0;

  // 0 1 -> 1
  *((*nn).InputValue +2) = 0;
  *((*nn).InputValue +3) = 1;
  *((*nn).OutputValue +1) = 1;

  // 1 0 -> 1
  *((*nn).InputValue +4) = 1;
  *((*nn).InputValue +5) = 0;
  *((*nn).OutputValue +2) = 1;

  // 1 1 -> 0
  *((*nn).InputValue +6) = 1;
  *((*nn).InputValue +7) = 1;
  *((*nn).OutputValue +3) = 0;

  //Initialize weight and bias randomly
  //deltas are initialized to 0
  for (int i = 0;i< (*nn).nbInput; i++)
  {
    for (int j = 0; j < (*nn).nbLayer; j++)
    {
      *((*nn).WeightIH + (j + i * (*nn).nbLayer)) = Random();
      *((*nn).deltaWeightIH + (j + i * (*nn).nbLayer)) = 0.0;
    }
  }

  for (int i = 0; i < (*nn).nbLayer; i++)
  {
    *((*nn).WeightHO + i) = Random();
    *((*nn).deltaWeightHO + i) = 0.0;
    *((*nn).BiasH + i) = Random();
    *((*nn).deltaBiasH + i) = 0.0;
  }
  (*nn).deltaBiasO= 0.0;
}

void FeedForward(struct Network *nn, int p, int epoch, int patt)
{

  // feedforward between input and hidden layer

  for (int i = 0; i <  (*nn).nbLayer; i++)
  {
    double sum_ih = 0.0;
    for (int j = 0; j < (*nn).nbInput; j++)
    {
      sum_ih += *((*nn).WeightIH + (i + j *(*nn).nbLayer)) * 
                *((*nn).InputValue + (j + p *(*nn).nbInput));
    }
    *((*nn).OutputH + i) = sigmoid(sum_ih +  *((*nn).BiasH + i));
    // the output is the output value of sigmoid
    // sigmoid = sum of (weight * input) + bias
  }

  // feedforward between hidden and output layer
  double sum_ho = 0;
  for (int i = 0; i < (*nn).nbLayer; i++)
  {
    sum_ho += *((*nn).WeightHO + i) * *((*nn).OutputH + i);
  }
  (*nn).OutputO = sigmoid(sum_ho + (*nn).BiasO);
// it is the output of the output layer, so we do not need to put *

  if (patt == p)
  { // save the outputO of the inputs
  (*nn).Output_p = (*nn).OutputO;
  }

  //error calculation
  (*nn).Error += 0.5 * ( *((*nn).OutputValue + p) - (*nn).OutputO) * 
                      (*((*nn).OutputValue + p) - (*nn).OutputO);

  // print the epoch, input and output values
  
  if (epoch % 100 == 0 && epoch < 1000)
  {
    /*printf("Inputs are %f and %f. Output is %f \n"
                    ,*((*nn).InputValue + p * 2)
                    ,*((*nn).InputValue + p * 2 +1)
                    , (*nn).OutputO);
  }
  else if (epoch % 500 == 0)
  {
    printf("Inputs are %f and %f. Output is %f \n"
                    ,*((*nn).InputValue + p * 2)
                    ,*((*nn).InputValue + p * 2 +1)
                    , (*nn).OutputO);*/
  }
}

void BackPropagation(struct Network *nn, int p)
{
  // backpropagation

  // calculation of the delta output
  (*nn).deltaOutputO = (*((*nn).OutputValue + p) - (*nn).OutputO) *
                      (*nn).OutputO * (1.0 - (*nn).OutputO);

  // sum of output's deltas
  for (int i = 0; i < (*nn).nbLayer; i++)
  {
    double dSumOutput = *((*nn).WeightHO + i) * (*nn).deltaOutputO ;

    *((*nn).deltaHidden + i) = dSumOutput * *((*nn).OutputH + i) * 
                            (1.0 - *((*nn).OutputH + i));
  }


  for (int i = 0; i < (*nn).nbLayer; i++)
  {
    // update hidden bias
    *((*nn).deltaBiasH + i) = (*nn).eta * *((*nn).deltaHidden + i);
    *((*nn).BiasH + i) += *((*nn).deltaBiasH + i) ;

    // update weight between input and hidden layers
    for (int j = 0; j < (*nn).nbInput; j++)
    {
      *((*nn).deltaWeightIH + (i + j * (*nn).nbLayer)) = 
	      (*nn).eta * *((*nn).InputValue + 
              (j + p * (*nn).nbInput)) * *((*nn).deltaHidden + i) + 
              (*nn).alpha * *((*nn).deltaWeightIH + (i + j * (*nn).nbLayer));

      *((*nn).WeightIH + (i + j * (*nn).nbLayer)) += 
	      *((*nn).deltaWeightIH + (i + j * (*nn).nbLayer));
    }
  }

  //update output bias
  (*nn).deltaBiasO = (*nn).eta * (*nn).deltaOutputO;
  (*nn).BiasO  += (*nn).deltaBiasO ;

  //update weight between hidden and output layers
  for (int i = 0; i < (*nn).nbLayer; i++)
  {
    *((*nn).deltaWeightHO + i) = (*nn).eta * *((*nn).OutputH + i) *
                              (*nn).deltaOutputO + (*nn).alpha *
                              *((*nn).deltaWeightHO + i);
    *((*nn).WeightHO + i) += *((*nn).deltaWeightHO + i) ;
  }

}

void TrainNetwork (struct Network *nn, int nbepoch, int nbp, int patt)
{
	// train the network, calling feedward and backpropagation

        for (int epoch = 1; epoch <= nbepoch; epoch++)
        {
                (*nn).Error = 0.0;

                //p refers to the pattern, 00 01 10 or 11
                for (int p = 0; p < nbp; p++)
                {
                        FeedForward(nn, p, epoch, patt);
                        BackPropagation(nn, p);
                }

		// print the epoch and the error rate

		/*if (epoch % 100 == 0 && epoch < 1000)
 		{
   			printf("Epoch %-5d : Error = %f \n",epoch,(*nn).Error);
 		}
  		else if (epoch % 500 == 0)
  		{
    			printf("Epoch %-5d : Error = %f \n",epoch,(*nn).Error);
  		}*/
	}
}


void XOR (int patt)
{
        int nbp = 4;
        int nbepoch = 5000;

        struct Network nn = Initialize_Net();
        struct Network *nn_p = &nn;

        Initialize_Val(nn_p);
        TrainNetwork(nn_p, nbepoch, nbp, patt);

	printf("The output value is %f with an error rate of %f.\n",
			(*nn_p).Output_p, (*nn_p).Error);

}

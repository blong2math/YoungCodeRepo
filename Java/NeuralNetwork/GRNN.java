package Prediction;

public class GRNN{
	
	private double [] sigmas;
	private double [][] means;
	private double [] altitudes;
	private int numRadiusBasisUnits;
	private int numDimensions;
	
	public GRNN(double[][] inputs, double[] outputs, int numSamples, int numDims){
		numRadiusBasisUnits = numSamples;
		numDimensions = numDims;
		
		sigmas = new double[numSamples];
		for(int i = 0; i < numSamples; i++){
			sigmas[i] = 0.83;
		}
		means = inputs;
		altitudes = outputs;
	}
	
	public double predict(double[] inputs){
		double output = 0;
		double sumRb = 0;
		double [] rb = new double[numRadiusBasisUnits];
		for(int i = 0; i < numRadiusBasisUnits; i++){
			double dist = 0;
			for(int j = 0; j < numDimensions; j++){
				dist += Math.pow(inputs[j] - means[i][j], 2);
			}
			rb[i] = RadiusBasis(Math.sqrt(dist), sigmas[i]);
			sumRb += rb[i];
		}
		for(int i = 0; i < numRadiusBasisUnits; i++){
			output += altitudes[i] * rb[i] / sumRb;
		}
		return output + 70;
	}
	
	public void train(){
		
	}
	
	private double RadiusBasis(double dist, double sigma){
		return Math.exp(-dist * dist / (2 * sigma * sigma));
	}
}
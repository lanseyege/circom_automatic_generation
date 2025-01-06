pragma circom 2.0.0;

template Multiplier () {
	signal input x; 
	signal output out_0; 
	out_0 <== x * x;
	signal output out_1; 
	out_1 <== out_0 * x;
	signal input a; 
	signal output out_2; 
	out_2 <== a * out_1;
	signal input b; 
	signal output out_3; 
	out_3 <== b * out_0;
	signal output out_4; 
	out_4 <== out_2 + out_3;
	signal input c; 
	signal output out_5; 
	out_5 <== c * x;
	signal output out_6; 
	out_6 <== out_4 + out_5;
	signal output out_7; 
	out_7 <== out_6 + 5;
}

component main = Multiplier();
pragma circom 2.0.0;

template Multiplier () {
signal input c; 
signal input b; 
signal output out_0; 
out_0 <== c * b;
signal input out_0; 
signal input a1; 
signal output out_1; 
out_1 <== out_0 + a1;
}

component main = Multiplier();
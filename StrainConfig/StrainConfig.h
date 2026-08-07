#ifndef STRAIN_CONFIG_H
#define STRAIN_CONFIG_H

// ---- Pins ----
#define DOUT  2
#define SCK   3

// ---- Beam geometry (cantilever tube) ----
const float OD = 1.0;      // in
const float WALL = 0.035;  // in
const float GAUGE_DIST = 3.0; // in, distance from fixed end
const float E_STEEL = 29007547.55; // psi, 4130 steel

// ---- Gauge properties ----
const float GAUGE_FACTOR = 2.0;   // from gauge datasheet (unknown)
const float R_GAUGE = 261.5;      // ohms

// ---- find using calbration program results, update constants ----
// counts per microstrain, determined empirically
const float COUNTS_PER_MICROSTRAIN = -6690.06007; 

// counts per pound, determined empirically
const float COUNTS_PER_LB = -8147.72522;

#endif
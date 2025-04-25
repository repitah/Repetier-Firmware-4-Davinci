#!/usr/bin/env python

import math, numpy as np, matplotlib.pyplot as plt


# Vref---R2---+---RT---gnd
#             |
#             +---R1---gnd
#             |
#            Vadc

class Thermistor:

  def __init__ (self, R0_Ω, T0_C, β_K, R1, R2):
    self.β_K = β_K
    self.Ri = (R1 * R2) / (R1 + R2)
    self.Kv = 4096 * R1 / (R1 + R2)
    self.const = R0_Ω / math.exp (β_K / (T0_C + 273.15))

  def resistance (self, T_C):
    return self.const * math.exp (self.β_K / (T_C + 273.15)) 

  def adc (self, T_C, RT_Ω=None):
    if RT_Ω is None: RT_Ω = self.resistance (T_C)
    return round (self.Kv * RT_Ω / (RT_Ω + self.Ri))


class DaVinci10E3Dv6 (Thermistor):

  def __init__ (self):
    #Use an extremely large R1 value if there is no parallel resistor to the thermistor 
    Thermistor.__init__ (self, 100000, 25, 3950, 10000000000, 33000)
    # Resistance values are 0.0 as they will be calculated as the script runs.
    # Plug the actual spec sheet (if available) values into the orignal D10-E3Dv6-ThermistorTable.py script
    self.table = (
        (-20, 0.0),
        (-10, 0.0),
        (  0, 0.0),
        ( 10, 0.0),
        ( 20, 0.0),
        ( 30, 0.0),
        ( 40, 0.0),
        ( 50, 0.0),
        ( 60, 0.0),
        ( 70, 0.0),
        ( 80, 0.0),
        ( 90, 0.0),
        (100, 0.0),
        (110, 0.0),
        (120, 0.0),
        (130, 0.0),
        (140, 0.0),
        (150, 0.0),
        (160, 0.0))

  def print_map (self):
    print ('#define EXT0_TEMPSENSOR_TYPE 7')
    print (f'#define NUM_TEMPS_USERTHERMISTOR2 {len(self.table)}')
    print ('#define USER_THERMISTORTABLE2 {', end = '')
    for t, r in reversed(self.table):
      r = self.resistance(t)
      a = self.adc(t, r) 
      print (f'{{{a},{t*8}}},', end='')
    print ('}')


if __name__ == '__main__':

  t = DaVinci10E3Dv6 ()
  t.print_map()

  print ('R@-20 =', t.resistance (-20), t.adc(-20))
  print ('R@25  =', t.resistance (25),  t.adc(25))
  print ('R@300 =', t.resistance (300), t.adc(300))

  #x = np.linspace (-20, 160, 10)
  #y = [t.adc(i) for i in x]
  #plt.plot(x, y)
  #plt.grid()
  #plt.show()


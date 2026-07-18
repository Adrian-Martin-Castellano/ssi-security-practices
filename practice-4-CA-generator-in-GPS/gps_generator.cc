// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Course: 3rd
// Practice 4: SSI
// Author: Adrián Martín Castellano
// Email: alu0101547619@ull.edu.es
// Date: 25/02/2025

#include <iostream>
#include <vector>
#include <bitset>
#include <cstdlib>

#define BLUE    "\033[34m"
#define RESET   "\033[0m"
#define GREEN   "\033[32m"

/**
 * @brief Data structure containing the phase selector taps for the 32 GPS satellites.
 */
const std::vector<std::pair<int, int>> satellite_taps = {{
    {2, 6}, {3, 7}, {4, 8}, {5, 9}, {1, 9}, {2, 10}, {1, 8}, {2, 9},
    {3, 10}, {2, 3}, {3, 4}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10},
    {1, 4}, {2, 5}, {3, 6}, {4, 7}, {5, 8}, {6, 9}, {1, 3}, {4, 6},
    {5, 7}, {6, 8}, {7, 9}, {8, 10}, {1, 6}, {2, 7}, {3, 8}, {4, 9}
}};

/**
 * @brief Generates and visualizes the GPS C/A PRN sequence step-by-step.
 * @param satellite_id Chosen satellite ID (1 to 32).
 * @param sequence_length Total bits to generate and trace.
 */
void GenerateGoldCode(int satellite_id, int sequence_length) {
  std::bitset<10> lfsr1_state("1111111111"), lfsr2_state = lfsr1_state;
  std::bitset<10> lfsr1_feedback_reg, lfsr2_feedback_reg, aux_fb1, aux_fb2;
  lfsr1_feedback_reg[0] = 0, lfsr2_feedback_reg = lfsr1_feedback_reg;

  std::cout << "   LFSR1    | Feedback |    LFSR2    | Feedback | C/A PRN Sequence" << std::endl;
  std::cout << "------------+----------+-------------+----------+-----------------" << std::endl;

  while (sequence_length > 0) {
    // Print LFSR1 shifting state
    for (int i = lfsr1_state.size() - 1; i >= 0 ; i--) {
      if (i != 0 && i != 7) std::cout << lfsr1_state[i];
      else std::cout << GREEN << lfsr1_state[i] << RESET;
    }
    std::cout << "  |    " << aux_fb1[0] << "     |  "; 

    // Print LFSR2 shifting state
    for (int i = lfsr2_state.size() - 1; i >= 0 ; i--) {
      if (i != 0 && i != 7 && i != 1 && i != 2 && i != 4 && i != 8) std::cout << lfsr2_state[i];
      else std::cout << GREEN << lfsr2_state[i] << RESET;
    }
    std::cout << "  |    " << aux_fb2[0] << "     | ";

    // GPS C/A Code selection logic via XORing selected satellite taps
    std::bitset<1> g2_selected_tap = lfsr2_state[abs((satellite_taps[satellite_id - 1].first) - 10)] ^ 
                                     lfsr2_state[abs((satellite_taps[satellite_id - 1].second) - 10)];
    std::bitset<1> prn_output_bit = g2_selected_tap[0] ^ lfsr1_state[0];

    std::cout << "        " << BLUE << prn_output_bit << RESET << std::endl;

    // Shift LFSR1 and inject feedback bit
    lfsr1_state >>= 1;
    aux_fb1[0] = lfsr1_state[7] ^ lfsr1_state[0];
    lfsr1_state[9] = lfsr1_feedback_reg[0];
    lfsr1_feedback_reg = aux_fb1;

    // Shift LFSR2 and inject feedback bit
    lfsr2_state >>= 1;
    aux_fb2[0] = lfsr2_state[0] ^ lfsr2_state[1] ^ lfsr2_state[2] ^ lfsr2_state[4] ^ lfsr2_state[7] ^ lfsr2_state[8];
    lfsr2_state[9] = lfsr2_feedback_reg[0];
    lfsr2_feedback_reg = aux_fb2;

    sequence_length--;
  }
}

int main() {
  int satellite_id, sequence_length;
  std::cout << "Satellite ID (1-32): ";
  if (!(std::cin >> satellite_id) || satellite_id < 1 || satellite_id > 32) {
    std::cerr << "Invalid Satellite ID." << std::endl;
    return 1;
  }
  std::cout << "Output sequence length: ";
  std::cin >> sequence_length;

  GenerateGoldCode(satellite_id, sequence_length);
  return 0;
}
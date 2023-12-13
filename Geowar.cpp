#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cmath>
#include <ctime>
#include <cstdlib>

const double PI = 3.14159265358979323846; 
int direct_hits = 0;
int hits = 0;
int near_hits = 0;

const int field_size = 30;
const int num_enemies = 5;

std::vector<int> enemy_angles;
std::vector<std::pair<int, int>> enemy_coordinates;



void print_intro() {

  std::cout << "GEOWAR\n";
  std::cout << "CREATIVE COMPUTING\n"; 
  std::cout << "MORRISTOWN, NEW JERSEY\n\n";
  
  std::cout << "Do you want a description of the game? ";
  std::string a;
  std::cin >> a;

  if (a == "no") {
    return;
  } else {
    std::cout << "\n     THE FIRST QUADRANT OF A REGULAR COORDINATE GRAPH WILL" << std::endl;
    std::cout << " SERVE AS" << std::endl;
    std::cout << "THE BATTLEFIELD.  FIVE ENEMY INSTALLATIONS ARE LOCATED" << std::endl;
    std::cout << " WITHIN A" << std::endl;
    std::cout << "30 BY 30 UNIT AREA.  NO TARGET IS INSIDE THE 10 BY 10 " << std::endl;
    std::cout << "UNIT AREA" << std::endl;
    std::cout << "ADJACENT TO THE ORIGIN, AS THIS IS THE LOCATION OF OUR " << std::endl;
    std::cout << "BASE. WHEN" << std::endl;
    std::cout << "THE MACHINE ASKS FOR THE DEGREE OF THE SHOT, RESPOND " << std::endl;
    std::cout << "WITH A NUMBER" << std::endl;
    std::cout << "BETWEEN 1 AND 90." << std::endl;
    std::cout << "\n SCARE**********" << std::endl;
    std::cout << "    1. A DIRECT HIT IS A HIT WITHIN 1 DEGREE OF" << std::endl;
    std::cout << "*             *" << std::endl;
    std::cout << "        THE TARGET." << ", " << "*  HIT******  *" << std::endl;
    std::cout << "    2. A HIT MUST PASS BETWEEN THE FIRST SET OF" << std::endl;
    std::cout << "*  *       *  *" << std::endl;
    std::cout << "         INTEGRAL POINTS NW AND SE OF THE TARGET." << std::endl;
    std::cout << "*  *   D   *  *" << std::endl;
    std::cout << "    3. A SCARE MUST PASS BETWEEN THE NEXT SET OF" << std::endl;
    std::cout << "*  *       *  *" << std::endl;
    std::cout << "         INTEGRAL POINTS NW AND SE OF THE TARGET," << std::endl;
    std::cout << "*  ******HIT  *" << std::endl;
    std::cout << "         AND CAUSES THE ENEMY TO RELOCATE A " << std::endl;
    std::cout << "*             *" << std::endl;
    std::cout << "         MAXIMUM OF 1 UNIT IN ANY DIRECTION." << std::endl;
    std::cout << "**********SCARE\n\n";
    std::cout << "\n MISSILES HAVE INFINITE RANGE AND MAY HIT MORE THAN " << std::endl;
    std::cout << "ONE TARGET." << std::endl;
    std::cout << "A MISSILE THAT NEARLY MISSES AN INSTALLATION (A SCARE) " << std::endl;
    std::cout << "WILL BE" << std::endl;
    std::cout << "IMMEDIATELY SHOT DOWN.  ANY HITS BEFORE THIS TIME WILL " << std::endl;
    std::cout << "NOT BE COUNTED" << std::endl;
    std::cout << "UNLESS A DIRECT HIT WAS MADE.\n\n";
  
  }

}

void print_ready() {

  std::cout << "\nReady to go?\n\n";
  
  std::string b;
  std::cin >> b;

  if (b == "no") {
    std::cout << "Quitting game.\n"; 
    exit(0);

  std::cout << "\nGOOD LUCK!\n\n";
  }
}

void generate_enemy_coordinates() {

  for (int i = 0; i < num_enemies; i++) {

    int x = rand() % (field_size - 11) + 11;
    int y = rand() % (field_size - 11) + 11;

    enemy_coordinates.push_back({x, y});

  }

}

void calculate_angles() {

  for (int i = 0; i < enemy_coordinates.size(); i++) {

    int x = enemy_coordinates[i].first;
    int y = enemy_coordinates[i].second;

    enemy_angles.push_back(round(atan2(y, x) * 180 / PI));

  }

}

void is_hit(int degree) {

  int func_direct = 0;
  int func_hits = 0;
  int func_near = 0;
  int func_miss = 0;

  for (int i = 0; i < enemy_coordinates.size(); i++) {

    
    if (enemy_coordinates[i] == std::make_pair(0, 0))
      break;

    int diff = abs(enemy_angles[i] - degree);

    if (diff == 0) {
        
      direct_hits++;
      enemy_coordinates.erase(enemy_coordinates.begin() + i);
      enemy_angles.erase(enemy_angles.begin() + i);
            
      func_direct++;

    } else if (diff == 1) {

      hits++;
      enemy_coordinates.erase(enemy_coordinates.begin() + i);
      enemy_angles.erase(enemy_angles.begin() + i);
            
      func_hits++;

    } else if (diff == 2) {

      near_hits++;
      
      if (rand() % 2 == 0) {
        enemy_coordinates[i].first += (rand() % 2 == 0) ? -1 : 1;
      } else {
        enemy_coordinates[i].second += (rand() % 2 == 0) ? -1 : 1;
      }
      
      func_near++;

    }
    
    func_miss++;

  }

  std::cout << "Direct Hits: " << func_direct << ", Hits: " << func_hits << ", Scare: " << func_near << ", Missed: " << func_miss << std::endl;

}


void print_stats() {
  std::cout << "\nGame Over!\n";
  std::cout << "Stats:\n";
  std::cout << "Direct Hits: " << direct_hits << "\n";
  std::cout << "Hits: " << hits << "\n";
  std::cout << "Near Hits: " << near_hits << "\n";
}

int get_shot() {

  int degree;
  
  while (true) {
  
    std::cout << "Enter shot degree (0-90): ";
    
    if (std::cin >> degree) {
    
      if (degree >= 0 && degree <= 90) {
        return degree;  
      } else {
        std::cout << "Invalid input. Please enter an integer between 0-90.\n";
      }
      
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter an integer.\n"; 
    }
  
  }

}




int main() {

  srand( time( 0 ) );

  print_intro();

  start:  

  print_ready();

  generate_enemy_coordinates();

  calculate_angles();

  int degree;

  while (!enemy_coordinates.empty()) {

    int degree = get_shot();

    is_hit(degree);

  }
  
    print_stats();
    
    std::string play_again;
    std::cout << "\nWanna play again? (yes/no) ";
    std::cin >> play_again;

    if (play_again == "yes") {
        direct_hits = 0;
        hits = 0; 
        near_hits = 0;
        goto start;
    }

  return 0;

}
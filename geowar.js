const PI = 3.14159265358979323846; 
let direct_hits = 0;
let hits = 0;
let near_hits = 0;
const field_size = 30;
const num_enemies = 5;
let enemy_angles = [];
let enemy_coordinates = [];

function print_intro() {
  console.log("GEOWAR");
  console.log("CREATIVE COMPUTING");
  console.log("MORRISTOWN, NEW JERSEY\n");
  console.log("Do you want a description of the game? ");
  let a = prompt();
  if (a == "no") {
    return;
  } else {
    console.log("\n     THE FIRST QUADRANT OF A REGULAR COORDINATE GRAPH WILL");
    console.log(" SERVE AS");
    console.log("THE BATTLEFIELD.  FIVE ENEMY INSTALLATIONS ARE LOCATED");
    console.log(" WITHIN A");
    console.log("30 BY 30 UNIT AREA.  NO TARGET IS INSIDE THE 10 BY 10 ");
    console.log("UNIT AREA");
    console.log("ADJACENT TO THE ORIGIN, AS THIS IS THE LOCATION OF OUR ");
    console.log("BASE. WHEN");
    console.log("THE MACHINE ASKS FOR THE DEGREE OF THE SHOT, RESPOND ");
    console.log("WITH A NUMBER");
    console.log("BETWEEN 1 AND 90.");
    console.log("\n SCARE**********");
    console.log("    1. A DIRECT HIT IS A HIT WITHIN 1 DEGREE OF");
    console.log("*             *");
    console.log("        THE TARGET." + ", " + "*  HIT******  *");
    console.log("    2. A HIT MUST PASS BETWEEN THE FIRST SET OF");
    console.log("*  *       *  *");
    console.log("         INTEGRAL POINTS NW AND SE OF THE TARGET.");
    console.log("*  *   D   *  *");
    console.log("    3. A SCARE MUST PASS BETWEEN THE NEXT SET OF");
    console.log("*  *       *  *");
    console.log("         INTEGRAL POINTS NW AND SE OF THE TARGET,");
    console.log("*  ******HIT  *");
    console.log("         AND CAUSES THE ENEMY TO RELOCATE A ");
    console.log("*             *");
    console.log("         MAXIMUM OF 1 UNIT IN ANY DIRECTION.");
    console.log("**********SCARE\n\n");
    console.log("\n MISSILES HAVE INFINITE RANGE AND MAY HIT MORE THAN ");
    console.log("ONE TARGET.");
    console.log("A MISSILE THAT NEARLY MISSES AN INSTALLATION (A SCARE) ");
    console.log("WILL BE");
    console.log("IMMEDIATELY SHOT DOWN.  ANY HITS BEFORE THIS TIME WILL ");
    console.log("NOT BE COUNTED");
    console.log("UNLESS A DIRECT HIT WAS MADE.\n\n");
  }
}

function print_ready() {
  console.log("\nReady to go?\n\n");
  let b = prompt();
  if (b == "no") {
    console.log("Quitting game.\n"); 
    return;
  }
  console.log("\nGOOD LUCK!\n\n");
}

function generate_enemy_coordinates() {
  for (let i = 0; i < num_enemies; i++) {
    let x = Math.floor(Math.random() * (field_size - 11)) + 11;
    let y = Math.floor(Math.random() * (field_size - 11)) + 11;
    enemy_coordinates.push([x, y]);
  }
}

function calculate_angles() {
  for (let i = 0; i < enemy_coordinates.length; i++) {
    let x = enemy_coordinates[i][0];
    let y = enemy_coordinates[i][1];
    enemy_angles.push(Math.round(Math.atan2(y, x) * 180 / PI));
  }
}

function is_hit(degree) {
  let func_direct = 0;
  let func_hits = 0;
  let func_near = 0;
  let func_miss = 0;
  for (let i = 0; i < enemy_coordinates.length; i++) {
    if (enemy_coordinates[i][0] == 0 && enemy_coordinates[i][1] == 0)
      break;
    let diff = Math.abs(enemy_angles[i] - degree);
    if (diff == 0) {
      direct_hits++;
      enemy_coordinates.splice(i, 1);
      enemy_angles.splice(i, 1);
      func_direct++;
    } else if (diff == 1) {
      hits++;
      enemy_coordinates.splice(i, 1);
      enemy_angles.splice(i, 1);
      func_hits++;
    } else if (diff == 2) {
      near_hits++;
      if (Math.random() < 0.5) {
        enemy_coordinates[i][0] += (Math.random() < 0.5) ? -1 : 1;
      } else {
        enemy_coordinates[i][1] += (Math.random() < 0.5) ? -1 : 1;
      }
      func_near++;
    }
    func_miss++;
  }
  console.log("Direct Hits: " + func_direct + ", Hits: " + func_hits + ", Scare: " + func_near + ", Missed: " + func_miss);
}

function print_stats() {
  console.log("\nGame Over!\n");
  console.log("Stats:");
  console.log("Direct Hits: " + direct_hits);
  console.log("Hits: " + hits);
  console.log("Near Hits: " + near_hits);
}

function get_shot() {
  let degree;
  while (true) {
    console.log("Enter shot degree (0-90): ");
    degree = parseInt(prompt());
    if (!isNaN(degree) && degree >= 0 && degree <= 90) {
      return degree;  
    } else {
      console.log("Invalid input. Please enter an integer between 0-90.\n");
    }
  }
}

function main() {
  
  print_intro();
  start:  
  print_ready();
  generate_enemy_coordinates();
  calculate_angles();
  let degree;
  while (enemy_coordinates.length > 0) {
    degree = get_shot();
    is_hit(degree);
  }
  print_stats();
  let play_again;
  console.log("\nWanna play again? (yes/no) ");
  play_again = prompt();
  if (play_again == "yes") {
    direct_hits = 0;
    hits = 0; 
    near_hits = 0;
  }
}

main();



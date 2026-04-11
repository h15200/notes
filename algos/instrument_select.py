# logic for random seeding the Forest music app
# all of this happens on game start to pre-compute the final instrumentation

import random
import time
from enum import Enum
from itertools import combinations

class Instrument(str, Enum):
    FLUTE = "FLUTE"
    CLARINET = "CLARINET"
    TENOR_SAX = "TENOR SAX"
    VIOLIN = "VIOLIN"
    VIOLA = "VIOLA"
    CELLO = "CELLO"
    DOUBLE_BASS = "BASS"
    TRUMPET = "TRUMPET"
    FRENCH_HORN = "FRENCH HORN"
    TROMBONE = "TROMBONE"
    SNARE_DRUM = "SNARE DRUM"
    BASS_DRUM = "BASS DRUM"

# Groups defined as static data
GROUPS = {
    "HIGH": [Instrument.FLUTE, Instrument.CLARINET, Instrument.VIOLIN, Instrument.VIOLA, Instrument.TRUMPET],
    "MIDDLE": [Instrument.CLARINET, Instrument.TENOR_SAX, Instrument.VIOLA, Instrument.FRENCH_HORN, Instrument.TROMBONE],
    "LOW": [Instrument.CLARINET, Instrument.TENOR_SAX, Instrument.VIOLA, Instrument.CELLO, Instrument.DOUBLE_BASS, Instrument.FRENCH_HORN, Instrument.TROMBONE],
    "DRUMS": [Instrument.SNARE_DRUM, Instrument.BASS_DRUM]
}

def calculate_permutations() -> int:
    """
    Calculates total unique instrument combinations.
    Since order doesn't matter, this is a combination problem.
    Constraint: Must have at least one from HIGH, MIDDLE, and LOW.
    """
    all_instruments = list(Instrument)
    total_valid = 0
    
    # Check every possible subset of the 12 instruments (2^12 = 4096)
    for i in range(1, len(all_instruments) + 1):
        for combo in combinations(all_instruments, i):
            has_high = any(ins in GROUPS["HIGH"] for ins in combo)
            has_mid = any(ins in GROUPS["MIDDLE"] for ins in combo)
            has_low = any(ins in GROUPS["LOW"] for ins in combo)
            
            if has_high and has_mid and has_low:
                total_valid += 1
    return total_valid

def pick_from(category: str, shuffled_pools: dict, available: set, final_instrumentation: dict) -> bool:
    """Picks the next available instrument from a category. Returns True if successful."""
    pool = shuffled_pools[category]
    while pool:
        selection = pool.pop()
        if selection in available:
            available.remove(selection)
            final_instrumentation[category].append(selection.value)
            return True
    return False

def generate_ensemble():
    # Efficiency: Use a set for O(1) availability checks
    available = set(Instrument)
    # Track selections by category for cleaner output
    final_instrumentation = {cat: [] for cat in GROUPS}

    # Efficiency: Pre-shuffle groups so we can just use pop() for O(1) selection
    random.seed(time.time())
    shuffled_pools = {cat: random.sample(members, len(members)) for cat, members in GROUPS.items()}

    # 1. Pick 3 starters: one from HIGH, MIDDLE, and LOW to ensure balance
    for cat in ["HIGH", "MIDDLE", "LOW"]:
        pick_from(cat, shuffled_pools, available, final_instrumentation)

    # 2. Add random number of extra players (0-9)
    num_to_add = random.randint(0, 9)
    print(f"--- Seeding logic: Starting with Trio (H/M/L) + {num_to_add} added players ---")

    cycle = ["DRUMS", "LOW", "HIGH", "MIDDLE"]
    for i in range(num_to_add):
        # Round-robin through groups; if one is empty, continue to the next in the list
        found = False
        for j in range(len(cycle)):
            cat_to_try = cycle[(i + j) % len(cycle)]
            if pick_from(cat_to_try, shuffled_pools, available, final_instrumentation):
                found = True
                break
        if not found:
            break

    # 3. Format and print the final instrumentation
    output = [f"{cat} [{', '.join(instruments)}]" for cat, instruments in final_instrumentation.items() if instruments]
    print("\n" + " | ".join(output) + "\n")

if __name__ == "__main__":
    total_combos = calculate_permutations()
    print("Welcome to Forest Music Seeder")
    print(f"Total possible unique instrumentations (satisfying H/M/L constraint): {total_combos}")
    try:
        while True:
            input("Press Enter to create a new instrumentation (or Ctrl+C to exit)...")
            generate_ensemble()
    except KeyboardInterrupt:
        print("\nExiting...")

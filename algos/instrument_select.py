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
PAID_GROUPS = {
    "HIGH": [Instrument.FLUTE, Instrument.CLARINET, Instrument.VIOLIN, Instrument.VIOLA, Instrument.TRUMPET],
    "MIDDLE": [Instrument.CLARINET, Instrument.TENOR_SAX, Instrument.VIOLA, Instrument.FRENCH_HORN, Instrument.TROMBONE],
    "LOW": [Instrument.CLARINET, Instrument.TENOR_SAX, Instrument.VIOLA, Instrument.CELLO, Instrument.DOUBLE_BASS, Instrument.FRENCH_HORN, Instrument.TROMBONE],
    "DRUMS": [Instrument.SNARE_DRUM, Instrument.BASS_DRUM]
}

FREE_INSTRUMENTS = [Instrument.VIOLIN, Instrument.TROMBONE, Instrument.CLARINET, Instrument.CELLO]
FREE_GROUPS = {
    "HIGH": [Instrument.VIOLIN, Instrument.CLARINET],
    "MIDDLE": [Instrument.TROMBONE, Instrument.CLARINET],
    "LOW": [Instrument.TROMBONE, Instrument.CLARINET, Instrument.CELLO]
}

def calculate_instrumentation_combinations(instruments: list, min_size: int, max_size: int) -> int:
    """
    Calculates total unique instrument sets (combinations) based purely on count,
    without any role constraints (as if there were no HIGH/MIDDLE/LOW logic).
    """
    total = 0
    for i in range(min_size, max_size + 1):
        import math
        total += math.comb(len(instruments), i)
    return total

def pick_from(category: str, shuffled_pools: dict, available: set, final_instrumentation: dict) -> bool:
    """Picks the next available instrument from a category. Returns True if successful."""
    pool = shuffled_pools.get(category, [])
    while pool:
        selection = pool.pop()
        if selection in available:
            available.remove(selection)
            final_instrumentation[category].append(selection.value)
            return True
    return False

def generate_ensemble(version: str):
    if version == 'F':
        instruments = FREE_INSTRUMENTS
        groups = FREE_GROUPS
        max_extra = 1
        print("\n--- Generating FREE Version Ensemble (Max 4 Players) ---")
    else:
        instruments = list(Instrument)
        groups = PAID_GROUPS
        max_extra = 9
        print("\n--- Generating PAID Version Ensemble (Max 12 Players) ---")

    available = set(instruments)
    final_instrumentation = {cat: [] for cat in groups}
    random.seed(time.time())
    shuffled_pools = {cat: random.sample(members, len(members)) for cat, members in groups.items()}

    # 1. Pick 3 starters
    for cat in ["HIGH", "MIDDLE", "LOW"]:
        if cat in groups:
            pick_from(cat, shuffled_pools, available, final_instrumentation)

    # 2. Add random extra players
    num_to_add = random.randint(0, max_extra)
    print(f"Seeding logic: Starting with Trio (H/M/L) + {num_to_add} added players")

    cycle = [cat for cat in groups]
    for i in range(num_to_add):
        found = False
        for j in range(len(cycle)):
            cat_to_try = cycle[(i + j) % len(cycle)]
            if pick_from(cat_to_try, shuffled_pools, available, final_instrumentation):
                found = True
                break
        if not found:
            break

    # 3. Print the final instrumentation
    output = [f"{cat} [{', '.join(instruments)}]" for cat, instruments in final_instrumentation.items() if instruments]
    print(" | ".join(output) + "\n")

if __name__ == "__main__":
    paid_instrumentation = calculate_instrumentation_combinations(list(Instrument), 3, 12)
    free_instrumentation = calculate_instrumentation_combinations(FREE_INSTRUMENTS, 3, 4)
    
    print("Welcome to Forest Music Seeder")
    print("To make a valid ensemble, we need at least 1 of High, Middle, and Low parts. Some instruments can play multiple parts. The percussion groups are optional and not necessary. \nWith this in mind..")
    print("\nFREE VERSION ANALYSIS:")
    print("- Instruments: Violin, Trombone, Clarinet, Cello")
    print("- Possible ensemble size: 3 or 4")
    print(f"- Combination of instrumentation: {free_instrumentation}")

    print("\nPAID VERSION ANALYSIS:")
    print(f"- Number of instruments: {len(Instrument)}")
    print("- Possible ensemble size: 3 to 12")
    print(f"- Combination of instrumentation: {paid_instrumentation}!!! (value proposition!)")

    try:
        while True:
            choice = input("\nRandomize [P]aid version or [F]ree version? (or Ctrl+C to exit): ").strip().upper()
            if choice in ['P', 'F']:
                generate_ensemble(choice)
            else:
                print("Invalid choice. Please enter 'P' or 'F'.")
    except KeyboardInterrupt:
        print("\nExiting...")

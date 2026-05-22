# Mixing/Mastering for a children's game app audio using LogicPro

- The goal is to have -18~-16db of INTEGRATED LUFS (Loudness) so all audio samples feel even and clear. We want to do this without distoring the original sound or having a huge range of dynamics as you won't pick up soft notes on a mobile/tablet speaker.

  ***

  tdlr; On individual track strip [gain adjustment, EQ, Compressor, Saturation, Reverb], on Stereo out strip [limiter, Loudness metering]

  Phase 0: The Setup (Clean Slate on individual strip)
  - Mixer Fader: Click "X" to open mixer, and on the individual track that we're working with, set to 0.0 dB. Remember that fader peak metering INCLUDES all plugins.
  - Plugins: Bypass all plugins initially to monitor the raw signal.
  - Stereo Out: Place a Loudness Meter at the very end to track your progress.

  Phase 1: Gain Staging (The Foundation on individual strip)
  - Plugin: Utility > Gain (First slot).
  - Action: Adjust the Gain knob until the track meter peaks at -6.0 dBFS.
  - Why: This creates "Headroom." It’s loud enough for plugins to work but far enough from the "Red" to avoid clipping. Remember to bypass all individual plugins

  Phase 2: Cleaning (ChannelEQ on individual strip)
  - Action: Channel EQ.
  - High Pass Filter: Set to 150Hz (cuts mud/breath/rumble by 24db).
  - Corrective Dip: Dip 2-3dB at 3kHz (smooths harsh violin/flute bite).
  - Slight 1-2db boost on 2-4kHz
  - Low Pass Filter: Everything above 12kHz also cut 24db

  Phase 3: Leveling (Compressor on individual strip)
  - Model: Platinum DIgital
  - Make sure signal coming in (input meter on the left) is reflecting what you set the gain to in phase 1. This is just a sanity check.
  - Note that there are 2 places labeled "Threshold"
  - Main Threshold (on the lower left hand): Lower until you see 3–5 dB of Gain Reduction (GR). If you see more, raise this.
  - Limiter Threshold (on the right side): Set to -1.0 dB (CRITICAL: Do not leave at -10dB or it will "choke" the sound).
  - Auto Gain: OFF.

  Phase 4: Thickening (Saturation via Phat FX on individual strip)
  - This may not even be necessary if the source sound is rich
  - Modules: Turn every submodule OFF except Distortion and Master.
  - Distortion Slot 1: Soft Saturation (1–15%) — Shaves the sharpest peaks.
  - Distortion Slot 2: Tube (1–10%) — Adds harmonic warmth and "body."
  - Distortion Slot 3: Exciter (1–5%) — Adds sparkle for small speakers.
  - Master Module: Set to Soft Limiting.
  - Why: This closes the gap between your "Peak" and "Loudness," making the song feel louder without the meters jumping higher.

  Phase 5: Depth (Reverb on individual strip)
  - Action: Apply Reverb (Space Designer or ChromaVerb).
  - Wet/Dry: Keep Wet below 20%.
  - Output: Ensure the reverb "tails" don't push the track meter into the Red.

  Phase 6: Final Target (Adaptive Limiter on Stereo strip, Loudness metering on Stereo strip)
  - Location: Last plugin on the Stereo Out.
  - Out Ceiling: -1.0 dB.
  - True Peak Detection: ON.
  - Gain Knob: Slowly increase (usually +1.0 to +3.0 dB) until the Integrated LUFS hits -18.
  - Note that we WANT the limiter to do the last 1-3 db of boost. If it is already at the high limit of -16db, go back to PhatFX and remove some percentages
  - Success Metric: Your song is loud, clear, and the mixer stays in the Yellow!

  - You can copy all plugins in the mix view by right clicking on "settings" and "copy", then multi-select other strips and right click again on one of their "settings", and "paste plugins only"

  ***

  Key Discoveries for your Notes:
  1.  Crest Factor: If peaks are at -5 but LUFS is at -20, the signal is too "spiky." Saturation and Compression fix this by "shaving" peaks and "lifting" the body.
  2.  The -10dB Trap: Never let an internal plugin limiter (like the one in the Compressor) stay at -10dB; it acts as an invisible wall that prevents you from reaching professional loudness.
  3.  The 2-dB Rule: It is better to let the final Limiter do 1–2 dB of the "lifting" rather than trying to make the instruments hit -18 LUFS on their own. This keeps the mix sounding "glued" and professional.

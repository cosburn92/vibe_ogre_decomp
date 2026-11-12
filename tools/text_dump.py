#!/usr/bin/env python3
"""Dump the game's dialogue/message files (extracted/lha/serifu*.bin, Serifu_*.bin) as text.

Message file: u32 BE offsets to the messages (count = first offset / 4), then the messages as
NUL-terminated ASCII with inline control codes. Some messages are untranslated Japanese left in the
US ROM, in Shift-JIS (decoded here as cp932). The meanings below
are inferred from how the codes are used in the text, not yet from the game's text engine:

  @n          newline
  @p          wait for a button, then next page (usually followed by @c)
  @c          clear the box
  @a, @s      end-of-message waits
  @k @m @u    speaker header: the speaker's name runs up to the next @n
  @F<3 digits> speaker header with a portrait number
  @l<digit>   text colour (@l0 resets), e.g. "@l2Dragon Helm@l0"
  @%<d> @&<dd> @!<d> @z<d>   insert a variable (e.g. the leader's name)
  @T<3 digits> @t<3 digits>  timed pause
  @1 @2 @w<4 digits> @#     answer choices / branches
  @*          tutorial text
  @= @- @x @r @A @S<d>      window and layout setup (unknown details)
  {T<2 digits>}  a special glyph: {T05} is an ellipsis; func_801A17AC_ovl_071280 writes {T09}

usage: python3 tools/text_dump.py [--plain] [file ...]   # default: every serifu file
  --plain  render @n as newlines, @p as a page break, {T05} as "...", and drop the other codes
"""
import glob
import os
import re
import struct
import sys

CODE = re.compile(r"@(?:F\d{3}|T\d{3}|t\d{3}|w\d{4}|&\d\d|[%!z]\d|l\d|S\d|.)")


def messages(data):
    first, = struct.unpack_from(">I", data, 0)
    offs = struct.unpack_from(f">{first // 4}I", data, 0)
    for o in offs:
        end = data.find(b"\0", o)
        raw = data[o:end if end >= 0 else len(data)]
        # ASCII, plus Shift-JIS for the Japanese lines left in the US ROM
        yield raw.decode("cp932", errors="backslashreplace")


def plain(text):
    text = text.replace("{T05}", "...")

    def repl(m):
        c = m.group(0)
        if c == "@n":
            return "\n"
        if c == "@p":
            return "\n--\n"
        if c[1] in "%&!z":
            return "<" + c[1:] + ">"
        return ""
    return CODE.sub(repl, text)


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    args = sys.argv[1:]
    as_plain = "--plain" in args
    files = [a for a in args if a != "--plain"] or sorted(
        glob.glob("extracted/lha/serifu*.bin") + glob.glob("extracted/lha/Serifu*.bin"))
    for path in files:
        data = open(path, "rb").read()
        print(f"=== {os.path.basename(path)}")
        for i, msg in enumerate(messages(data)):
            print(f"[{i}]")
            print(plain(msg) if as_plain else msg)
    return 0


if __name__ == "__main__":
    sys.exit(main())

////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2006 - 2016, Paul Beckingham, Federico Hernandez.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#include <cmake.h>
#include <Datetime.h>
#include <format.h>

////////////////////////////////////////////////////////////////////////////////
Datetime::Datetime ()
{
  clear ();
  _date = time (nullptr);
}

////////////////////////////////////////////////////////////////////////////////
Datetime::Datetime (const std::string& input, const std::string& format)
{
  clear ();
  std::string::size_type start = 0;
  if (! parse (input, start, format))
    throw ::format ("'{1}' is not a valid date in the '{2}' format.", input, format);
}

////////////////////////////////////////////////////////////////////////////////
bool Datetime::parse (
  const std::string& input,
  std::string::size_type& start,
  const std::string& format)
{
  auto i = start;
  Pig pig (input);
  if (i)
    pig.skip (i);

  // Parse epoch first, as it's the most common scenario.
  if (parse_epoch (pig))
  {
    // ::validate and ::resolve are not needed in this case.
    start = pig.cursor ();
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
void Datetime::clear ()
{
  _date            = 0;
}

////////////////////////////////////////////////////////////////////////////////
// Valid epoch values are unsigned integers after 1980-01-01T00:00:00Z. This
// restriction means that '12' will not be identified as an epoch date.
bool Datetime::parse_epoch (Pig& pig)
{
  return false;
}

////////////////////////////////////////////////////////////////////////////////
time_t Datetime::toEpoch () const
{
  return _date;
}



////////////////////////////////////////////////////////////////////////////////

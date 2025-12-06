#!/bin/bash
cat \
  <(echo '
{
  Version: "1"
  Segments: [
    {
      Name: Default
      CodeLabels: [  
  ') \
  <(awk '{print "{\nAddress: \""substr($2, 3) "\"\nName: " $3"\n}"}' woorm.lbl) \
  <(echo '
      ]
    }
  ]
}
  ') \
> woorm.labels

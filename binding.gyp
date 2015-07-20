{
  "targets": [
    {
      "target_name": "mathaka",
      "sources": [ "mathaka.cc" ],
      "include_dirs": [ "<!(node -e \"require('nan')\")" ]
    }
  ]
}

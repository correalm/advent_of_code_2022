package day7

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

type File struct {
  name string
  size int
}

type Dir struct {
  name string
  parent *Dir
  childrens []*Dir
  files []File
}

const (
  COMMAND_CD = "cd"
  COMMAND_BACK = ".."
  COMMAND_LS = "ls"
)

func newFile(name string, size int) File {
  var file File

  file.name = name
  file.size = size

  return file
}

func newDir(name string, parent *Dir) *Dir {
  var dir Dir

  dir.name = name
  dir.parent = parent

  return &dir
}

func day7(path string) int {
  file, err := os.Open(path)

  defer file.Close()

  if err != nil {
    return 0
  }

  scanner := bufio.NewScanner(file)
  scanner.Split(bufio.ScanLines)

  var root Dir
  root.name = "root"
  root.parent = nil

  current_dir := &root

  for scanner.Scan() {
    line := scanner.Text()
    fmt.Println(line)

    match, _ := regexp.MatchString(`[0-9]`, line)

    if match {
      tokens := strings.Split(line, " ")

      size, _ := strconv.Atoi(tokens[0])

      current_dir.files = append(current_dir.files, newFile(tokens[1], size))

      // fmt.Println(current_dir.files, "SIZE -> ", size, "Name -> ", tokens[1])
    }

    is_command, _ := regexp.MatchString(`\$`, line)

    if is_command {
      tokens := strings.Split(line, " ")

      // ISTO ESTA UMA BOSTA! REFATORAR
      change_dir := (strings.Compare(tokens[1], COMMAND_CD) == 0) && (strings.Compare(tokens[2], COMMAND_BACK) != 0)

      if change_dir {
        dir := newDir(tokens[2], current_dir)

        current_dir.childrens = append(current_dir.childrens, dir)

        // fmt.Println("CURRENT AFTER APPEND: ", len(current_dir.childrens), "Name: ", current_dir.name, "NEW DIR: ", dir.name, "ROOT CHILDRENS: ", len(root.childrens))
        current_dir = dir
      } else {
        if (strings.Compare(tokens[1], COMMAND_BACK) == 0) {
          current_dir = current_dir.parent
        }
      }
    }
  }
  
  for i := range root.childrens {
    for j := range root.childrens[i].childrens {
      for z := range root.childrens[i].childrens[j].childrens {
        fmt.Println("Path: ", root.childrens[i].name, root.childrens[i].childrens[j].name, root.childrens[i].childrens[j].childrens[z].name, "FILES: ", root.childrens[i].childrens[j].childrens[z].files[0].size)
      }
    }
  }

  return 1
}

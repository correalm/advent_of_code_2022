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
  size int64
  childrens []*Dir
  files []File
}

type ExplorerCallback func(dir *Dir)

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
  dir.size = 0
  dir.parent = parent

  return &dir
}

func explorer(dir *Dir, callback ExplorerCallback) {
  if len(dir.childrens) == 0 {
    callback(dir)
  }

  for i := range dir.childrens {
    current_dir := dir.childrens[i]

    if len(current_dir.childrens) > 0 {
      explorer(current_dir, callback)
    }

    callback(current_dir)
  }
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

      file := newFile(tokens[1], size)
      current_dir.files = append(current_dir.files, file)

      current_dir.size = current_dir.size + int64(file.size)

      if current_dir.parent != nil {
        current_dir.parent.size = current_dir.parent.size + current_dir.size
      }
    }

    is_command, _ := regexp.MatchString(`\$`, line)

    if is_command {
      tokens := strings.Split(line, " ")

      // ISTO ESTA UMA BOSTA! REFATORAR
      change_dir := (strings.Compare(tokens[1], COMMAND_CD) == 0) && (strings.Compare(tokens[2], COMMAND_BACK) != 0)

      if change_dir {
        dir := newDir(tokens[2], current_dir)

        current_dir.childrens = append(current_dir.childrens, dir)

        current_dir = dir
      } else {
        if (strings.Compare(tokens[1], COMMAND_BACK) == 0) {
          current_dir = current_dir.parent
        }
      }
    }
  }
  
  explorer(
    &root,
    func (dir *Dir) {
      fmt.Printf("DIR %s has %d files | SIZE: %d \n", dir.name, len(dir.files), dir.size)
    },
  )

  return 1
}

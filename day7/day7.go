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

func newFile(name string, size int) File {
  var file File

  file.name = name
  file.size = size

  return file
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
  root.name = "/"
  root.parent = nil

  current_dir := root

  for scanner.Scan() {

    line := scanner.Text()
    fmt.Println(line)

    match, _ := regexp.MatchString(`[0-9]`, line)

    if match {
      tokens := strings.Split(line, " ")

      size, _ := strconv.Atoi(tokens[0])

      current_dir.files = append(current_dir.files, newFile(tokens[1], size))

      fmt.Println(current_dir.files, "SIZE -> ", size, "Name -> ", tokens[1])
    }


    // if strings.Contains(line, "dir") {
    //   tokens := strings.Split(line, " ")

    //   fmt.Println("Dir name: ", tokens[1])
    // }

  }

  return 1
}

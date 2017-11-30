import React, { Component } from 'react'
import Radium from 'radium'

const styles = {
  root: {
  },
  title: {
    fontFamily: "'Oswald', sans-serif",
    fontSize: 46,
    fontWeight: 'bold',
    margin: '150px 0 10px',
  },
}

class Home extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <div style={styles.title}>Your home secured by JARVIS</div>
      </div>
    )
  }
}

export default Radium(Home)

import React, { Component } from 'react'
import Radium from 'radium'

class Dashboard extends Component {
  state = {}

  render() {
    return (
      <div>
        <div>Door</div>
        <div>Alarm</div>
        <div>Door</div>
      </div>
    )
  }
}

export default Radium(Dashboard)

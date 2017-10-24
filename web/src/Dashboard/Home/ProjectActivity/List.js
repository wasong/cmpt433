import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import Activity from './Activity'

const styles = {
  root: {
    overflowY: 'auto',
    height: '100%',
  },
}

const List = props => (
  <div style={styles.root}>
    <Activity label="Lights" value={70} />
    <Activity label="Temperature (Celsius)" value={35} />
    <Activity label="Measurement 3" value={70} />
    <Activity label="Analytic 4" value={70} />
  </div>
)

List.propTypes = {}
List.defaultProps = {}

export default Radium(List)

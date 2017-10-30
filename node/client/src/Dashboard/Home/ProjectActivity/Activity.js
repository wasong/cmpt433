import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import LinearProgress from 'material-ui/LinearProgress'

const styles = {
  root: {
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'space-between',
    padding: '40px 0',
  },
  label: {
    width: '30%',
    margin: '0 20px 0 0',
  },
}

// TODO: read value from something
const Activity = ({ label, value }) => (
  <div style={styles.root}>
    <div style={styles.label}>{label}</div>
    <LinearProgress mode="determinate" value={value} />
  </div>
)

Activity.propTypes = {}
Activity.defaultProps = {}

export default Radium(Activity)
